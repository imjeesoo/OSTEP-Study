# xv6-riscv Scheduler Modification  
## MLFQ (Multi-Level Feedback Queue) Implementation


## 1. Overview

기본 xv6 커널은 모든 프로세스에 동일한 시간 할당량을 부여하는  
Round Robin(RR) 스케줄링 방식을 사용한다.

하지만 실제 환경에서는 I/O Bound 작업과 CPU Bound 작업이 혼재되어 있으며,  
이를 효율적으로 처리하기 위해 우선순위 기반의 스케줄링이 필요하다.

본 프로젝트에서는 MLFQ(Multi-Level Feedback Queue) 정책을 도입하여,  
프로세스의 CPU 사용 패턴에 따라 우선순위를 동적으로 조정하고  
시스템의 응답성과 공정성을 개선하는 과정을 구현하였다.



## 2. Objectives

- Round Robin 스케줄러의 한계 이해
- MLFQ 알고리즘 설계 및 xv6에 적용
- 타이머 인터럽트 기반 CPU 사용량 추적
- 우선순위 강등(Demotion) 및 Boosting 구현
- 사용자 프로그램을 통한 동작 검증



## 3. Implementation

### (1) PCB (Process Control Block) 확장
-kernel/proc.h

int priority;     
// 0 (High), 1 (Medium), 2 (Low)  
int ticks_used;   
// 현재 큐에서 사용한 CPU 시간  
   
프로세스별 우선순위 및 CPU 사용량 추적  
  
### (2) Scheduler 구조 수정  
kernel/proc.c  
  
scheduler() 함수 수정  
Strict Priority 방식 적용  
  
동작:  
Priority 0 → 1 → 2 순으로 탐색  
상위 큐에 runnable 프로세스 존재 시 하위 큐는 실행되지 않음  
실행 후 항상 최상위 큐부터 재탐색  
  
### (3) Demotion (우선순위 강등)  
yield() 함수에서 처리  
Priority 0 → 4 ticks  
Priority 1 → 8 ticks  
Priority 2 → 16 ticks  
할당된 time quantum 초과 시  
→ 다음 레벨로 강등  
    
### (4) Priority Boosting (기아 방지)  
전역 변수 total_ticks 사용
일정 주기 (1000 ticks)마다 모든 프로세스 priority = 0으로 초기화  
→ starvation 방지  
  
### (5) Timer Interrupt 연동  
  
kernel/trap.c  
  
p->ticks_used++;  
total_ticks++;  
CPU 사용량을 실시간으로 반영  
  
### (6) 사용자 테스트 프로그램  
  
user/mlfqtest.c

CPU 연산 루프 실행  
우선순위 변화 확인  
  
## 4. Modified Files  
  
kernel/proc.h  
kernel/proc.c  
kernel/trap.c  
user/mlfqtest.c  
  
## 5. Result  
  
초기 실행 시 High priority에서 시작  
CPU 사용량 증가에 따라 Low priority로 강등  
이후 하위 큐에서 지속적으로 실행됨  
  
## 6. Conclusion
이론으로 접했던 MLFQ(Multi-Level Feedback Queue) 스케줄링 정책을  
xv6 커널에서 코드로 구현하고 검증하는 과정을 통해,  
스케줄링 정책이 실제 시스템 내에서 어떻게 동작하는지를  
코드 수준에서 명확히 이해할 수 있었다.  
  
ticks_used를 기반으로 한 실행 기록 관리와  
이를 이용한 우선순위 조정 과정에서  
MLFQ의 핵심인 Feedback 메커니즘을 직접 구현하였다.  
  
또한 타이머 인터럽트와 스케줄링 정책이 결합되는 구조를 통해  
커널 내부 동작이 유기적으로 연결되어 있음을 확인하였다.  
  

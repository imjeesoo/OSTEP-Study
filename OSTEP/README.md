# OS Measurement Operations

운영체제의 핵심 메커니즘인 시스템 콜(System Call)과 문맥 전환(Context Switch)의 비용을 직접 측정하고 분석한 실습 기록입니다.

##  Index

### 1. cost of a systemcall
   - 실험 목표: User 모드에서 Kernel 모드로의 단순 진입 비용 측정
   - 측정 방법: `getpid()` 반복 호출 및 `clock_gettime()` 정밀 측정
   - 결론: 일반 함수 호출보다 시스템 콜이 모드 전환으로 인해 더 높은 오버헤드를 가짐을 확인

### 2. context switch overhead
   - 실험 목표: 두 프로세스 간 CPU 제어권이 교체되는 문맥 전환 비용 측정
   - 측정 방법: Pipe 통신(Blocking) 유도 및 `sched_setaffinity()`를 이용한 단일 코어 고정 실험
   - 결론: 문맥 전환 비용(약 1.46μs)이 시스템 콜 비용보다 훨씬 크며, 프로세스 상태 보존/복구 비용이 성능의 주요 변수임을 실측함


## 실험 환경
- OS: Ubuntu (VMware Virtual Machine)
- CPU Affinity: 단일 코어(Core 0) 고정 측정
- Language: C
- Compiler: GCC
- Time Measuring: `clock_gettime` 

## References
- Operating Systems: Three Easy Pieces (Chapter 6: Limited Direct Execution)

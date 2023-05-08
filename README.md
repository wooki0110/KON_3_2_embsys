# 3학년 2학기 embedsystem rasp4b-Linux

## Final project

### 개인 식별과 개인별 운동상태를 통한 음악 추천 프로그램

#### Linux driver file 개발
(1) touch device
(2) dot matrix

#### Raspberry AI
(1) tensorflow object detection 사용 - reaspberry 4에 탑재
- 개인별 약 2000장에 달하는 여러 얼굴사진을 DB로 사용
- tensorflow에서 학습 후 모델을 추출하여 사용

- object detection은 얼굴 식별을 할 수 없는 알고리즘
- 사람 식별으로 변경 필요(추후 프로젝트)
- 개인용 DB로만 사용

(2) 운동상태 식별 - raspberry zero에 탑재
- 심장 박동, 자이로 위치 센서 사용
- label로 각 운동상태를 지정
- 운동상태에 따라 음악 장르를 지정

- DB에 문제가 발생
- 정확도가 높지 않음

(3) python 파일 사용
- 외부 명령으로 모든 device driver, socket 통신 한 파일에서 동작
- socket 통신은 3개 사용
- rsapberry 4 to raspberry 0 & raspberry 0 to pc

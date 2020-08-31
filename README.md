# DES
Data Encryption Standard

###  <strong>This Program make as Cryptogrphy Alorithm Assignment</strong>
이 프로그램은 암호알고리즘의 과제로써 ECB모드로 구현되었습니다.

---

## 구현
- 대칭키 암호시스템인 DES는 56비트 + 8비트의 패딩을 이용해서 64비트의 키를 가집니다. 

- 초기치환 -> 32비트씩 분리 -> 16라운드 f함수 연산 및 SubKey 생성 -> 최종치환 과정으로 이루어져있습니다

- Fesitel Network 구조로 32비트씩 나뉘어 Key에 의해 생성된 [Subkey](https://github.com/kococo-code/DES/blob/master/source.cpp#L128)가 매 라운드별로 [F함수](https://github.com/kococo-code/DES/blob/master/source.cpp#L113)에 의해 확장, 치환과정을 진행합니다.
 
 - Subkey는 PC_1 전치 표, PC_2 축약 표에 의해 이루어 집니다.

 - 복호화는 암호화의 역과정을 16라운드 거치면 복호화가 이루어 집니다.
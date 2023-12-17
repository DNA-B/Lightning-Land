# ⚡ Lightning-Land ⚡
![image](https://github.com/DNA-B/Lightning-Land/assets/102334596/ae31bf99-bee5-4281-9366-2e4aec4e208d)  
> **Trading program by Linux socket communication**

<br/><br/>

## 🗂 Project structure 🗂  

📦Lightning-Land  
┣ 📂data  
┃ ┗ 📜LL_data.txt  
┣ 📂header  
┃ ┣ 📜data_init.h  
┃ ┗ 📜data_save.h  
┣ 📂shmfile  
┃ ┣ 📜data_shmfile  
┃ ┗ 📜exit_cnt_shmfile  
┣ 📂source  
┃ ┣ 📜client.c  
┃ ┣ 📜data_init.c  
┃ ┣ 📜data_save.c  
┃ ┗ 📜server.c  
┣ 📜Makefile  
┗ 📜README.md  

<br/><br/>

## 🔎 Preview 🔍  
1. **서버와 클라이언트 접속**  
![image](https://github.com/DNA-B/Lightning-Land/assets/102334596/d1fcebe0-97ae-4926-b851-eff05d713448)  

2. **1인 통신**  
  
    2-1. 1인 통신시에 거래 성공 case  
    ![image](https://github.com/DNA-B/Lightning-Land/assets/102334596/8e89059a-3672-43bd-87d0-efd3c9eec07e)  

    2-2. 1인 통신시에 거래 실패 case  
    ![image](https://github.com/DNA-B/Lightning-Land/assets/102334596/68968f5d-8222-4590-ba0d-ad4700956cc0)  

    2-3. 이미 판매된 물건을 선택 → 다른 물건 구매를 원하지 않음 → 종료  
    ![image](https://github.com/DNA-B/Lightning-Land/assets/102334596/0a79f40c-b9bf-4409-af22-e12c1ab97972)  

    2-4. 엉뚱한 물건 번호를 고른 case  
    ![image](https://github.com/DNA-B/Lightning-Land/assets/102334596/91d67e4d-97c0-4db4-9975-9e0a3c5f686e)  

3. **다인 통신**  
  
    3-1. 다인 통신 시, 서로 다른 물건을 거래하는 case  
    ![image](https://github.com/DNA-B/Lightning-Land/assets/102334596/d21b4a97-3f76-498a-8f6d-2d74245cb1d4)  

    3-2. 다인 통신 시, 서로 같은 물건을 거래하는 case  
    ![image](https://github.com/DNA-B/Lightning-Land/assets/102334596/fcf425c7-ad95-4aca-bde3-df1ea8ac493d)  

    3-3. 다인 통신 시, 같은 물건을 골랐는데 구매자1(클라이언트1)이 거래에 실패해서 구매자2가 기다렸다가 거래에 성공한 case  
    ![image](https://github.com/DNA-B/Lightning-Land/assets/102334596/7d43f5c2-907f-4b99-8639-c379fde5e441)  

    3-4. 다인 통신 시, 구매자1과 구매자2가 같은 물건을 선택했을 경우, 구매자1의 거래가 완료될 때까지 구매자2가 거래를 대기하는 case  
    ![image](https://github.com/DNA-B/Lightning-Land/assets/102334596/7a6598af-bf02-4775-bb8d-fc0a2eeca59d)  
    ![image](https://github.com/DNA-B/Lightning-Land/assets/102334596/17621619-e387-4509-9b0c-8afc8d0f8583)  

4. **물건이 다 판매되었을 때**  
![image](https://github.com/DNA-B/Lightning-Land/assets/102334596/4b38edd6-386f-41cc-bf64-f3b4a92750c7)  

<br/><br/>

## 📈 To improvements 📈  
　The information on the item you want to sell is stored in a text file. Since the sale is carried out with a pre-stored file, you must enter the information of the item in the LL_data.txt file one by one in order to sell an item other than the stored item.  
　Additionally, when it comes to the Nego system, when different buyers want to purchase the same item, the seller will want to make a deal with the one who offers the higher price between the two buyers, even if both are higher than the minimum amount.  
　However, if buyer 1 who has already entered the transaction because that part was not implemented, the transaction succeeds and ends if the amount is simply higher than the minimum price. This remains a point of improvement.

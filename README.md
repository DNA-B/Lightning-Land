<div align="center">
  <h1>⚡ Lightning-Land ⚡</h1>
    <div>
      <img align="center" src="https://github.com/DNA-B/Lightning-Land/assets/102334596/ae31bf99-bee5-4281-9366-2e4aec4e208d"><br>
      <b> &gt; Trading program by Linux socket communication</b>
    </div>
  
<br/><br/>

  <h2>🗂 Project structure 🗂</h2>
  <div align="left"> 
    
    📦 
    ├─ Makefile
    ├─ README.md
    ├─ data
    │  └─ LL_data.txt
    ├─ header
    │  ├─ data_init.h
    │  └─ data_save.h
    ├─ shmfile
    │  ├─ data_shmfile
    │  └─ exit_cnt_shmfile
    └─ source
       ├─ client.c
       ├─ data_init.c
       ├─ data_save.c
       └─ server.c
  </div>
     

<br/><br/>

  <h2>🔎 Preview 🔍</h2>
  <h3><b>1. Server and client connections</b></h3>
    <div>
      <img src="https://github.com/DNA-B/Lightning-Land/assets/102334596/d1fcebe0-97ae-4926-b851-eff05d713448"><br>
    </div>
    
<br/>

  <h3><b>2. single communication</b></h3>
    <div>
      &ltSuccessful transaction case at the time of one person communication&gt<br>
      <img src="https://github.com/DNA-B/Lightning-Land/assets/102334596/8e89059a-3672-43bd-87d0-efd3c9eec07e"><br><br>
      Transaction failure case at the time of one person communication&gt<br>
      <img src="https://github.com/DNA-B/Lightning-Land/assets/102334596/68968f5d-8222-4590-ba0d-ad4700956cc0"><br><br>
      &ltSelect an item that has already been sold → Don't want to buy another item → Shut down&gt<br>
      <img src="https://github.com/DNA-B/Lightning-Land/assets/102334596/0a79f40c-b9bf-4409-af22-e12c1ab97972"><br><br>
      &ltCase of choosing the wrong item number&gt<br>
      <img src="https://github.com/DNA-B/Lightning-Land/assets/102334596/91d67e4d-97c0-4db4-9975-9e0a3c5f686e"><br><br>
    </div>
    
<br/>

  <h3><b>3. multiple communications</b></h3>
    <div>
        &ltIn multi-person communication, a case of trading different things&gt<br>
        <img src="https://github.com/DNA-B/Lightning-Land/assets/102334596/d21b4a97-3f76-498a-8f6d-2d74245cb1d4"><br>
      <br>
        &ltIn multi-person communication, a case of trading the same thing&gt<br>
        <img src="https://github.com/DNA-B/Lightning-Land/assets/102334596/fcf425c7-ad95-4aca-bde3-df1ea8ac493d"><br>
      <br>
        &ltIn the case of multi-person communication, the same item was selected, but Client 1 failed the transaction, so Client 2 waited and succeeded in the transaction&gt<br>
        <img src="https://github.com/DNA-B/Lightning-Land/assets/102334596/7d43f5c2-907f-4b99-8639-c379fde5e441"><br>
      <br>
        &ltIn multi-person communication, if Client 1 and Client 2 select the same item, Client 2 waits for the transaction to be completed&gt<br>
        <img src="https://github.com/DNA-B/Lightning-Land/assets/102334596/7a6598af-bf02-4775-bb8d-fc0a2eeca59d"><br>
        <img src="https://github.com/DNA-B/Lightning-Land/assets/102334596/17621619-e387-4509-9b0c-8afc8d0f8583"><br>
    </div>
    
<br/>

  <h3><b>4. when the goods are sold out</b><h3>
    <img src="https://github.com/DNA-B/Lightning-Land/assets/102334596/4b38edd6-386f-41cc-bf64-f3b4a92750c7">
    
<br/><br/>

  <h2>🐞 Usage 🐞</h2>
  <div>
    <code>make all</code><br><br>
    # terminal on<br>
    <code>./server</code><br><br>
    # another terminal on<br>
    <code>./client</code>
  </div>

<br><br>

  <h2>📈 To improvements 📈</h2>
    <div>
      The information on the item you want to sell is stored in a text file. Since the sale is carried out with a pre-stored file, you must enter the information of the item in the LL_data.txt file one by one in order to sell an item other than the stored item.  
    　Additionally, when it comes to the Nego system, when different buyers want to purchase the same item, the seller will want to make a deal with the one who offers the higher price between the two buyers, even if both are higher than the minimum amount.  
    　However, if buyer 1 who has already entered the transaction because that part was not implemented, the transaction succeeds and ends if the amount is simply higher than the minimum price. This remains a point of improvement.
    </div>
</div>

<br><br><br><br><hr>
<b><i>2023-12-02 ~ 2023-12-15</i></b>

# ROBOT_AK1
去建立一個自己的人形機器人，使其可以行走、活動

2025/3開始
![S__2048022_0](https://github.com/user-attachments/assets/7a1c39c9-b899-4503-aa96-95f224dfc2eb)

![S__2048021_0](https://github.com/user-attachments/assets/d046a25a-0102-425e-8ee8-c3aa52cd8d9f)

![S__2048023_0](https://github.com/user-attachments/assets/38ac85d2-4b34-49c7-a92e-8df05e8bb76c)

![S__2048006_0](https://github.com/user-attachments/assets/5b4119b7-8390-419f-b9ba-92e3ad9b924f)

打印了手臂、填充馬達，參考檔案為13年前的專案，改動其選用的無人機馬達，選用便宜馬達作為捲線器
選擇馬達為MW996馬達搭配pca16路驅動版去做驅動

![S__2048007_0](https://github.com/user-attachments/assets/b9919a82-2b0e-4e65-a34d-44e8c5ded61a)
![S__2048008_0](https://github.com/user-attachments/assets/27a7fecc-7a3d-4ccb-bbca-d008f449b8ea)
![S__2048013_0](https://github.com/user-attachments/assets/2533fe1b-75fb-4db9-8439-9afea0afd864)

將其完整組裝並測試，初步測試發現內部捲線互相感擾。去除後正常運作，但發現驅動的馬達常常失去連線，還需檢查原因

https://github.com/user-attachments/assets/7381f966-83a9-41f5-81c3-a6b69b6cc32b


![S__2048011_0](https://github.com/user-attachments/assets/3eea3b92-2a75-4851-bde1-cd35c87422d3)
測試成功，但是手肘的馬達還需挑選，原先專案設計有影片但沒有具體型號和挑選資料
預計挑選別的機器人專案的關節、肩膀選擇

加入自己的生醫訊號理解搭配exg pill感測器進行肌肉訊號控制手臂張合

https://github.com/user-attachments/assets/b2657f96-c7da-4dd3-86bd-5c959d0d9f6a

找到全身開源機器人專案inmoov嘗試打印部分
![S__2048015_0](https://github.com/user-attachments/assets/fb8e4800-17ac-4b72-9254-0c4f131a3606)
發現其設計相當複雜而且使用馬達費用太高
挑選其餘機器人做自己的設計

2025/4
訂購馬達了，繼續打印頭部進行嘗試，頭部繼續參考inmoov機器人的部分，但想參考其早期設計較為簡單之頭部，可以方便我選用現有的攝影機和喇叭進行填充頭部

![S__2097183](https://github.com/user-attachments/assets/abd922b5-ecd4-46ac-abae-922a6ebde455)

![S__2195458](https://github.com/user-attachments/assets/e6926184-4708-4bbc-89f8-4e57a391283d)


找到近期的開源專案可以參考其肩膀與手軸的設計添加進入我的機器人
參考的是
https://red-rabbit-robotics.ghost.io/

https://red-rabbit-robotics.ghost.io/rx1-humanoid-servo-assembly-instruction/

選擇其設計的減速輪和ht3215馬達作為我的肩膀和手軸的選擇
但具體設計調整等馬達到貨後嘗試

![image](https://github.com/user-attachments/assets/85165f05-5d89-462f-9893-51e4967b61b3)

參考該專案的身體
訂購機器人鋁材做為身體骨架

4/18
目前打印頭蓋骨1/2，預計下周完成頭部外殼，打印脖子測試其轉頭是否可以運作，以及預計使用羅技相機作為眼睛

4/23
st3215馬達抵達，發現驅動需要特定驅動版，補採購，但是整體設計的馬達與行星輪組裝正常，唯獨m2 8mm螺絲買錯，買的頭太大，無法適配
機器人頭 頭蓋骨組裝完成，剩餘耳朵與後腦，完成後就可以開始添加攝影機嘗試辨識

鋁材抵達，明天開始組裝身體





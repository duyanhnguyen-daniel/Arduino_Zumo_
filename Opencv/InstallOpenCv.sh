#!/usr/bin/env bash

chmod +x *.sh
./download-opencv.sh
./install-deps.sh
./build-opencv.sh
cd ~/opencv/opencv-4.5.0/build
sudo make install

cd /home/pi/Desktop/Opencv
wget "https://upload.wikimedia.org/wikipedia/en/7/7d/Lenna_%28test_image%29.png" -O lenna.jpg
python3 test.py lenna.jpg


cd /tmp
wget https://project-downloads.drogon.net/wiringpi-latest.deb
sudo dpkg -i wiringpi-latest.deb
gpio -v
gpio readall

sudo usermod -a -G dialout pi
groups

FILE_PATH_UART="/boot/config.txt" 
search_text="enable_uart=1"
replace_text="enable_uart=0"

sudo sed -i "s/$search_text/$replace_text/" $FILE_PATH_UART
if [[ $?==true ]]
then
   echo "Configure UART done"
else
   echo "False"
fi

FILE_PATH_SERIAL=/boot/cmdline.txt
search_text_SERIAL="console=serial0,115200 "
replace_text_SERIAL=""
sudo sed -i "s/$search_text_SERIAL/$replace_text_SERIAL/" $FILE_PATH_SERIAL
if [[ $?==true ]]
then
	echo "Configure SERIAL done"
else
	echo "Text doesnot exist or Already changed SERIAL"
fi


#Create the agent

sudo eval"$(ssh-agent -s)"
sudo ssh-keygen -t ed25519 -C "ViARTKeyGen"
sudo ssh-add ~/.ssh/id_ed25519
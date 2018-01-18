//4911B Self-Check functions

int CheckDrive(int Side){
	if (Side == 1){//right drive
		return 1;
 }
 else if( Side == 2){//left drive
   return 2;
 }
 else {return 3;}
}

int CheckLift(){

}

int CheckClaw(){

}

void CheckAll(int FairBattery,int FairBackupBattery){
  int Good = 0;

  int	Battery = nAvgBatteryLevel;
	int BackupBat = BackupBatteryLevel;

	int Left = CheckDrive(1);
	int Right = CheckDrive(2);
	int Lift = CheckLift();
	int Claw = CheckClaw();

	//check battery
	if (Battery < FairBattery){//low battery
		//set servo
 }
 else{Good = 1}

 //check backup battery
 if(BackupBat < FairBackupBattery && Good == 1){//low backup battery
   //set servo
 }
 else{Good = 1}

}

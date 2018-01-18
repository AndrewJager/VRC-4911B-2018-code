/*
	4911B 2017 Autonomous functions
	Written by Andrew Jager
*/

void Reset(){
	//stop motors
  	motor[RightFront] = 0;
    motor[RightBack] = 0;
    motor[LeftFront] = 0;
    motor[LeftBack] = 0;

    //reset encoders and variables
    SensorValue[RightEncoder] = 0;
	  SensorValue[LeftEncoder] = 0;
}

void AutoDrive(int Distance, int Power, int Skew, int DelayTime)
{
	Reset();
	//SensorValue(RightEncoder) = 0;
	SensorValue(LeftEncoder) = 0;

	int DistanceDriven = 0;
if(Skew == 0){//drive "straight"
	while(DistanceDriven < Distance){
		DistanceDriven = SensorValue[LeftEncoder];
  	motor[RightFront] = Power;
    motor[RightBack] = Power;
    motor[LeftFront] = Power;
    motor[LeftBack] = Power;

}
 else if (Skew > 0){//skew Right
   while(DistanceDriven < Distance){
		DistanceDriven = SensorValue[LeftEncoder];
  	motor[RightFront] = (Power - Skew);
    motor[RightBack] = (Power - Skew);
    motor[LeftFront] = Power;
    motor[LeftBack] = Power;
  }
}
else if (Skew < 0){//skew left
	while(DistanceDriven < Distance){
		DistanceDriven = SensorValue[LeftEncoder];
  	motor[RightFront] = Power;
    motor[RightBack] = Power;
    motor[LeftFront] = (Power + Skew);
    motor[LeftBack] = (Power + Skew);
 }
 }
 Reset();
 DistanceDriven = 0;
 delay(DelayTime);
}

void AutoTurn(int Direction, int point, int Distance, int Power, int DelayTime)
{
	int DistanceDriven = 0;
	Reset();
 if (Direction == 1){//right turn
   if(point == 1){//both motors
    while (DistanceDriven < Distance){
    DistanceDriven = SensorValue[RightEncoder];
		motor[RightFront] = Power;
		motor[RightBack] = Power;
		motor[LeftFront] = -Power;
		motor[LeftBack] = -Power;
	}
  }
  else{//one motor
  	while (DistanceDriven < Distance){
  	DistanceDriven = SensorValue[RightEncoder];
		motor[RightFront] = Power;
		motor[RightBack] = Power;
		motor[LeftFront] = 0;
		motor[LeftBack] = 0;
  }
 }
}
 else if (Direction == 2){//left turn
   if(point == 1){//both motors
		while (DistanceDriven < Distance){
    DistanceDriven = SensorValue[LeftEncoder];
		motor[RightFront] = -Power;
		motor[RightBack] = -Power;
		motor[LeftFront] = Power;
		motor[LeftBack] = Power;
	}
  }
  else{//one motor
  	while (DistanceDriven < Distance){
		DistanceDriven = SensorValue[LeftEncoder];
		motor[RightFront] = 0;
		motor[RightBack] = 0;
		motor[LeftFront] = Power;
		motor[LeftBack] = Power;
  }
 }
}
Reset();
delay(DelayTime);
}

void AutoLift(int Target, int Power, int DelayTime)
{
	if (Target == 0)//all the way down
	{
		while (SensorValue[LeftGoalLimit] == false || SensorValue[RightGoalLimit] == false){
			if (SensorValue[LeftGoalLimit] == false){
				motor[LeftGoalLift] = Power;
			}
			else{motor[LeftGoalLift] = 0;}


			if (SensorValue[RightGoalLimit] == false){
				motor[RightGoalLift] = Power;
			}
			else{motor[RightGoalLift] = 0;}

	}
	motor[LeftGoalLift] = 0;
	motor[RightGoalLift] = 0;
 }
 else if (Target == 1)//all the way up
   {
		while (SensorValue[LeftGoalLimitB] == false || SensorValue[RightGoalLimitB] == false){
			if (SensorValue[LeftGoalLimitB] == false){
				motor[LeftGoalLift] = -Power;
			}
			else{motor[LeftGoalLift] = 0;}

			if (SensorValue[RightGoalLimitB] == false){
				motor[RightGoalLift] = -Power;
			}
			else{motor[RightGoalLift] = 0;}
	}
	motor[LeftGoalLift] = 0;
	motor[RightGoalLift] = 0;
 }
 else{//custom target
  motor[LeftGoalLift] = Power;
  motor[RightGoalLift] = Power;
  delay(Target);
  motor[LeftGoalLift] = 0;
  motor[RightGoalLift] = 0;
 }
 delay(DelayTime);
}

void DriveStraight(int Distance, int Power, int Skew, int Error, int DelayTime){
	Reset();
	int DistanceDriven = 0;
	if (Power > 0){
	while(SensorValue[LeftEncoder] < Distance || SensorValue[LeftEncoder] < Distance){
		DistanceDriven = (SensorValue[LeftEncoder] + SensorValue[LeftEncoder]) / 2;
		if (SensorValue[LeftEncoder] > (SensorValue[RightEncoder] + Error)){//left drive ahead
			motor[RightFront] = Power;
      motor[RightBack] = Power;
      motor[LeftFront] = Power - Skew;
      motor[LeftBack] = Power - Skew; //reduce left drive
	  }
  	else if (SensorValue[RightEncoder] > (SensorValue[LeftEncoder] + Error)){
  		motor[RightFront] = Power - Skew;
      motor[RightBack] = Power - Skew;//Reduce right drive
      motor[LeftFront] = Power;
      motor[LeftBack] = Power;
  }
  else{//drive normaly
  	motor[RightFront] = Power;
    motor[RightBack] = Power;
    motor[LeftFront] = Power;
    motor[LeftBack] = Power;
  }
}
}
else if (Power < 0){
	while(DistanceDriven < Distance){
		DistanceDriven = (SensorValue[LeftEncoder] + SensorValue[RightEncoder]) / 2;
		if (SensorValue[LeftEncoder] > (SensorValue[RightEncoder] + Error)){//left drive ahead
			motor[RightFront] = Power;
      motor[RightBack] = Power;
      motor[LeftFront] = Power + Skew;
      motor[LeftBack] = Power + Skew; //reduce left drive
	  }
  	else if (SensorValue[RightEncoder] > (SensorValue[LeftEncoder] + Error)){
  		motor[RightFront] = Power + Skew;
      motor[RightBack] = Power + Skew;//Reduce right drive
      motor[LeftFront] = Power;
      motor[LeftBack] = Power;
  }
  else{//drive normaly
  	motor[RightFront] = Power;
    motor[RightBack] = Power;
    motor[LeftFront] = Power;
    motor[LeftBack] = Power;
  }
}
}
//stop motors and wait
Reset();
delay(DelayTime);
}

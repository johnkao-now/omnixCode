if (turn == 1) {  
	if (checkSides(0)) {
      robotMove(3);
      myservo.write(90);
      delay(2000);
      robotMove(0);
      turn = 1;
    }
    else if (checkSides(1)) {
      robotMove(4);
      myservo.write(90);
      delay(2000);
      robotMove(0);
      turn = 0;
    }
} else if (turn == 1) { 
	if (checkSides(1)) {
      robotMove(4);
      myservo.write(90);
      delay(2000);
      robotMove(0);
      turn = 1;
    }
    else if (checkSides(0)) {
      robotMove(3);
      myservo.write(90);
      delay(2000);
      robotMove(0);
      turn = 0;
    }
}
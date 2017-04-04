long nLastXmitTimeStamp = nPgmTime;
long nDeltaTime         = 0;

bool changing_speed = false;
bool force_stopped = false;
float stop_speed_multiplier = 1.0;

const int kMaxSizeOfMessage = 30;
const int INBOX = 5;

void toggle_stop_robot() {
	if (!changing_speed) {
		force_stopped = !force_stopped;
	}
}

void handle_message(string msg) {
	if (msg == "UP") {
		enqueue_direction(FORWARD);
	} else if (msg == "DOWN") {
		enqueue_direction(TURNABOUT);
	} else if (msg == "LEFT") {
		enqueue_direction(LEFT);
	} else if (msg == "RIGHT") {
		enqueue_direction(RIGHT);
	} else if (msg == "FIRE") {
		toggle_stop_robot();
	} else if (msg == "A") {
		empty_queue(nav_queue);
	}
}

task start_stop_task() {
	while (1) {
		waitUntil(force_stopped);
		changing_speed = true;
		while (force_stopped && stop_speed_multiplier > 0) {
			stop_speed_multiplier -= 0.02;
			wait1Msec(10);
		}
		changing_speed = false;

		stop_speed_multiplier = 0;

		waitUntil(!force_stopped);
		changing_speed = true;
		while (!force_stopped && stop_speed_multiplier < 1) {
			stop_speed_multiplier += 0.02;
			wait1Msec(10);
		}
		changing_speed = false;

		stop_speed_multiplier = 1;
	}
}

task app_task() {
  TFileIOResult nBTCmdRdErrorStatus;
  int nSizeOfMessage;
  ubyte nRcvBuffer[kMaxSizeOfMessage];

  while (true) {
    nSizeOfMessage = cCmdMessageGetSize(INBOX);

    if (nSizeOfMessage > kMaxSizeOfMessage) {
    	nSizeOfMessage = kMaxSizeOfMessage;
  	}

  	if (nSizeOfMessage > 0){
  		nBTCmdRdErrorStatus = cCmdMessageRead(nRcvBuffer, nSizeOfMessage, INBOX);
  		nRcvBuffer[nSizeOfMessage] = '\0';
  		string s = "";
  		stringFromChars(s, (char *) nRcvBuffer);
  		displayCenteredBigTextLine(4, s);
  		handle_message(s);
  	}

  	wait1Msec(100);
	}
}

void init_app() {
	startTask(app_task);
	startTask(start_stop_task);
}

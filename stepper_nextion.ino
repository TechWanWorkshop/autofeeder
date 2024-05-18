#include <Stepper.h>
#include <Nextion.h>

const int steps_per_rev = 2048; 
#define IN1 26
#define IN2 25
#define IN3 33
#define IN4 32

int speed,rev, interval=5;

uint32_t next, next_interval;

//page 0
NexText sp = NexText(0,6,"ech");   
NexText re = NexText(0,5,"ecl");   
NexText in = NexText(0,10,"ect");   

NexButton p_start = NexButton(0,1,"b0");
NexButton p_stop = NexButton(0,2,"b1");

NexPicture pi0 = NexPicture(0,3,"p0");
NexPicture pi1 = NexPicture(0,4,"p1");

NexTouch *nex_listen_list[] = {
  &p_start,
  &p_stop,
  NULL
};


Stepper motor(steps_per_rev, IN1, IN2, IN3, IN4);

void p_start_release(void *ptr) {
  motor.setSpeed(speed);
  pi0.setPic(1);
  pi1.setPic(1);
  motor.step(rev);
  pi0.setPic(0);
  pi1.setPic(0);
}

void p_stop_release(void *ptr) {
  motor.step(0);
  pi0.setPic(0);
  pi1.setPic(0);
}


void setup()
{
  nexInit();
  p_start.attachPop(p_start_release, &p_start);
  p_stop.attachPop(p_stop_release, &p_stop);
  pi0.setPic(0);
  pi1.setPic(0);
  next = millis();
  next_interval = millis();
    
}

void loop() 
{
  nexLoop(nex_listen_list);

  if(millis() >= next) {
    get_nextion();
    next = millis()+500;
  }

  if(millis() >= next_interval) {
    
    if(interval>0) {
    motor.setSpeed(speed);
    pi0.setPic(1);
    pi1.setPic(1);
    motor.step(rev);
    pi0.setPic(0);
    pi1.setPic(0);
    }

    next_interval = millis()+interval;
    
  }
  
}

void get_nextion()
{


  char buffer[100] = {0};
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  sp.getText(buffer, sizeof(buffer));
  String s = String(buffer);
  speed = s.toInt();
  Serial.println(speed);

  
  re.getText(buffer1, sizeof(buffer1));
  String ss = String(buffer1);
  rev = ss.toInt();
  Serial.println(rev);

  in.getText(buffer2, sizeof(buffer2));
  String sss = String(buffer2);
  interval = sss.toInt();
  interval = interval*1000;
  Serial.println(interval);

}

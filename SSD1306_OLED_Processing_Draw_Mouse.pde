import processing.serial.*;
Serial volkan;
String x ,y;
String gidecek;
void setup() {
size(128, 64);
noSmooth();
fill(126);
background(102);
String portName = Serial.list()[0];
volkan=new Serial(this,portName,9600);

}

void draw() {
if (mousePressed) {
stroke(0);
line(mouseX-1, mouseY, mouseX+1, mouseY);
x=Integer.toString(mouseX);
y=Integer.toString(mouseY);
while(x.length()<3) {x='0'+x;}
while(y.length()<2) {y='0'+y;}
gidecek=x+y;
volkan.write(gidecek);
volkan.write('n');
print(gidecek);
print("n");
delay(100);
}
}

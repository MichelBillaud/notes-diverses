interface Element {
  void paint();
}

class Circle implements Element {
  float x, y;
  Circle(float x, float y) {
    this.x = x;
    this.y = y;
  }
  @Override
  void paint() {
    fill(255, 0, 0);
    ellipse(x, y, 20, 20);
  }
}


class Square implements Element {
  float x, y;
  Square(float x, float y) {
    this.x = x;
    this.y = y;
  }
  void paint() {
    fill(255, 255, 0);
    rectMode(CENTER);
    rect(x, y, 20, 20);
  }
}

ArrayList<Element> elements = new ArrayList<Element>();

void setup()
{
  size(300, 200);
}

void mousePressed() {
  if (mouseButton == LEFT) {
    elements.add(new Circle(mouseX, mouseY));
  } else {
    elements.add(new Square(mouseX, mouseY));
  }
}

void draw() 
{
  background(0);
  for (Element e : elements) {
    e.paint();
  }
}

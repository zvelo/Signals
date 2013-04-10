/*
 * Copyright 2009 Patrick Hogan
 * Updated by Joshua Rubin <jrubin@zvelo.com>
 *
 * Signals and Slots example code.
 */

#include <stdio.h>

#include "./Delegate.h"
#include "./Signal.h"

using ::zvelo::signals::Signal0;
using ::zvelo::signals::Signal1;
using ::zvelo::signals::Signal2;
using ::zvelo::signals::Delegate1;

class Button {
  public:
    Button()
    : update0(),
      update1(),
      update2() {}

    virtual ~Button() {}

    Signal0<void> update0;
    Signal1<int> update1;
    Signal2<int, float> update2;

    void ClickButton(void) {
      printf("update0\n");
      update0();

      printf("update1\n");
      update1(1);

      printf("update2\n");
      update2(2, 34.5);
    }
};

class Label {
  public:
    virtual ~Label() {}

    virtual void Update0(void) const {
      printf("Update0(void)\n");
    }

    void Update1(int i) {
      printf("Update1(%d)\n", i);
    }

    void Update2(int i, float f) {
      printf("Update2(%d, %.1f)\n", i, f);
    }

    static void Static(void) {
      printf("Static(void)\n");
    }
};


class Label2 : public Label {
  public:
    virtual void Update0(void) const {
      printf("virtual Update0(void)\n");
    }
};

void Global(void) {
  printf("Global(void)\n");
}


int main() {
  Label l;
  Label2 l2;
  Button b;

  // Test plain delegate
  Delegate1<int> delegate;
  delegate.Bind(&l, &Label::Update1);
  delegate(5);

  printf("delegate done\n");

  // Connect a bunch of signals
  b.update0.Connect(&l, &Label::Update0);  // zero parameter
  b.update2.Connect(&l, &Label::Update2);  // two parameters
  b.update0.Connect(&l2, &Label::Update0);  // virtual method
  b.update0.Connect(&Global);  // global function
  b.update0.Connect(&Label::Static);  // static method

  #define Connect(a, signal, b, slot) a.signal.Connect(&b, &slot)
  Connect(b, update1, l, Label::Update1);  // we could do QT style with a macro

  b.ClickButton();  // emit signals

  printf("Disconnect Update0, Update1 and Global\n");
  b.update0.Disconnect(&l, &Label::Update0);
  b.update0.Disconnect(&l2, &Label::Update0);
  b.update1.Disconnect(&l, &Label::Update1);
  b.update0.Disconnect(&Global);

  b.ClickButton();  // emit signals again, shouldn't see disconnected slots firing

  return EXIT_SUCCESS;
}

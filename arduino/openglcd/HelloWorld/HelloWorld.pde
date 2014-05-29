/*

  HelloWorld.pde
  
  GLCD Example

  m2tklib = Mini Interative Interface Toolkit Library
  
  Copyright (C) 2011  olikraus@gmail.com

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <openGLCD.h>		// inform Arduino IDE that we will use openGLCD library
#include "M2tk.h"
#include "m2ghopenglcd.h"

#include "fonts/System5x7.h"


M2_LABEL(hello_world_label, "f0", "Hello World");
M2tk m2(&hello_world_label, NULL, NULL, m2_gh_openglcd_bf);

void setup() {
  m2.setFont(0, System5x7);
}

void loop() {
  m2.draw();
  delay(1000);
}



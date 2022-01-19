/*
CS 349 A1 Skeleton Code - Snake

- - - - - - - - - - - - - - - - - - - - - -

Commands to compile and run:

    g++ -o snake snake.cpp -L/usr/X11R6/lib -lX11 -lstdc++
    ./snake

Note: the -L option and -lstdc++ may not be needed on some machines.
*/

#include <iostream>
#include <list>
#include <cstdlib>
#include <sys/time.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>
#include <cstring>
#include <sstream>



/*
 * Header files for X functions
 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

/*
 * Global game state variables
 */
const int Border = 1;
const int BufferSize = 20;
const int width = 800;
const int height = 600;
const int startlevel = 0;
//const int FPS = 10;

/*
 * Information to draw on the window.
 */
struct XInfo {
	Display	 *display;
	int		 screen;
	Window	 window;
	GC		 gc[3];
	int		width;		// size of window
	int		height;
  unsigned long colours[10];
};

struct Posn {
    int x;
    int y;
};

/*
 * Function to put out a message on error exits.
 */
void error( string str ) {
  cerr << str << endl;
  exit(0);
}



/*
 * An abstract class representing displayable things.
 */
class Displayable {
	public:
		virtual void paint(XInfo &xinfo) = 0;
};



class Obstacle : public Displayable {
public:
    virtual void paint(XInfo &xinfo) {
        if (level == 2) {
            XSetForeground(xinfo.display, xinfo.gc[0], xinfo.colours[9]);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 200, 20, 40, 460);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 240, 440, 280, 40);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 480, 280, 40, 160);

            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 600, 120, 40, 460);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 320, 120, 280, 40);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 320, 120, 40, 160);

            XSetForeground(xinfo.display, xinfo.gc[0], xinfo.colours[8]);

            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 200, 20, 5, 460);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 235, 20, 5, 420);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 200, 475, 320, 5);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 235, 440, 250, 5);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 480, 280, 5, 160);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 480, 280, 40, 5);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 515, 280, 5, 200);


            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 320, 120, 5, 160);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 320, 120, 320, 5);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 320, 275, 40, 5);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 360, 155, 5, 125);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 360, 155, 245, 5);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 600, 160, 5, 420);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 635, 120, 5, 460);

        } else if (level == 1) {
            XSetForeground(xinfo.display, xinfo.gc[0], xinfo.colours[9]);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 20, 180, 600, 40);

            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 180, 380, 600, 40);

            XSetForeground(xinfo.display, xinfo.gc[0], xinfo.colours[8]);

            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 20, 180, 600, 5);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 20, 215, 600, 5);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 615, 180, 5, 40);

            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 180, 380, 600, 5);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 180, 415, 600, 5);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 180, 380, 5, 40);

        }
    }

    Obstacle (int level = 0): level(level) {}

    void levelinc () {if (level != 2) level++;}

    void setlevel (int l) {level = l;}

    int getlevel() {return level;}

    bool notonob(int x, int y) {
        if (level == 1) {
            if (x >= 20 && x < 620) {
                if (y >= 180 && y < 220) {
                    return false;
                }
            }
            if (x >= 180 && x < 780) {
                if (y >= 380 && y < 420) {
                    return false;
                }
            }
        } else if (level == 2) {
            if (x >= 200 && x < 240) {
                if (y >= 20 && y < 480) {
                    return false;
                }
            }
            if (x >= 240 && x < 480) {
                if (y >= 440 && y < 480) {
                    return false;
                }
            }
            if (x >= 480 && x < 520) {
                if (y >= 280 && y < 480) {
                    return false;
                }
            }

            if (x >= 320 && x < 360) {
                if (y >= 120 && y < 280) {
                    return false;
                }
            }
            if (x >= 360 && x < 600) {
                if (y >= 120 && y < 160) {
                    return false;
                }
            }
            if (x >= 600 && x < 640) {
                if (y >= 120 && y < 580) {
                    return false;
                }
            }
        }
        return true;
    }

    private:
        int level; // level 0 no obstacle, level 1 easy obstacle, level 2, hard obstacle
};

Obstacle obstacle(startlevel);

class Snake : public Displayable {
	  public:
	    	virtual void paint(XInfo &xinfo) {
            for (int i = 0; i < body.size(); i++) {
                XSetForeground(xinfo.display, xinfo.gc[0], xinfo.colours[5]);
                XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0],
                body[i].x, body[i].y, blockSize, blockSize);

                XSetForeground(xinfo.display, xinfo.gc[0], xinfo.colours[1]);

                XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0],
                body[i].x, body[i].y, 2, 20);
                XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0],
                body[i].x, body[i].y, 20, 2);
                XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0],
                body[i].x + 18, body[i].y, 2, 20);
                XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0],
                body[i].x, body[i].y + 18, 20, 2);

            }
		    }

		    void move(XInfo &xinfo) {
            Posn head = body[0];
            Posn nhead;
            if (direction == 1) { // up move
                nhead.x = head.x;
                nhead.y = head.y - speed;
            } else if (direction == 2) { // down move
                nhead.x = head.x;
                nhead.y = head.y + speed;
            } else if (direction == 3) { // left move
                nhead.x = head.x - speed;
                nhead.y = head.y;
            } else { // right move
                nhead.x = head.x + speed;
                nhead.y = head.y;
            }
            Posn temp;
            temp.x = body[body.size() - 1].x;
            temp.y = body[body.size() - 1].y;
            for (int i = body.size() - 1; i > 0; i--) {
                body[i].x = body[i - 1].x;
                body[i].y = body[i - 1].y;
            }
            body[0].x = nhead.x;
            body[0].y = nhead.y;
            if (fruit) {
                body.push_back(temp);
            }
            fruit = false;

            int num;
            alive = check(num);
            int curlevel = obstacle.getlevel();

            if (!alive && curlevel == 2) {
                return;
            }

            int sizelen = body.size();
            if (sizelen % 2 == 0) {
                sizelen = sizelen / 2;
            } else {
                sizelen = sizelen / 2 + 1;
            }

            vector<Posn> tempbody;
            if (sizelen == 1) {
                tempbody.push_back(head);
            } else {
              for (int i = 0; i < sizelen; ++i) {
                  tempbody.push_back(body[i + 1]);
              }
            }
            if (!alive && blood > 0) {
                if (num > 0) {
                    for (int i = 0; i < body.size() - num; i++) {
                        body.pop_back();
                    }
                } else if (num == -1) { //left
                    body.clear();
                    for (int i = 0; i < sizelen; ++i) {
                        body.push_back(tempbody[i]);
                    }
                    if (curlevel == 0) {
                        if (body[0].y - 0 > 580 - body[0].y) {
                            direction = 1;
                        } else {
                            direction = 2;
                        }
                    } else if (curlevel == 1) {
                        if (body[0].y < 180) {
                            if (body[0].y - 0 > 160 - body[0].y) {
                                direction = 1;
                            } else {
                                direction = 2;
                            }
                        } else {
                            if (body[0].y - 220 > 580 - body[0].y) {
                                direction = 1;
                            } else {
                                direction = 2;
                            }
                        }
                    }
                } else if (num == -2) {// right
                    body.clear();
                    for (int i = 0; i < sizelen; ++i) {
                        body.push_back(tempbody[i]);
                    }
                    if (curlevel == 0) {
                        if (body[0].y - 0 > 580 - body[0].y) {
                            direction = 1;
                        } else {
                            direction = 2;
                        }
                    } else if (curlevel == 1) {
                        if (body[0].y < 380) {
                            if (body[0].y - 0 > 360 - body[0].y) {
                                direction = 1;
                            } else {
                                direction = 2;
                            }
                        } else {
                            if (body[0].y - 420 > 580 - body[0].y) {
                                direction = 1;
                            } else {
                                direction = 2;
                            }
                        }
                    }
                } else if (num == -3) { //up and down
                    body.clear();
                    for (int i = 0; i < sizelen; ++i) {
                        body.push_back(tempbody[i]);
                    }
                    if (curlevel == 0 || curlevel == 1) {
                        if (body[0].x - 0 > 780 - body[0].x) {
                            direction = 3;
                        } else {
                            direction = 4;
                        }
                    }
                } else if (num == -4) {
                    body.clear();
                    for (int i = 0; i < sizelen; ++i) {
                        body.push_back(tempbody[i]);
                    }
                    if (curlevel == 0 || curlevel == 1) {
                        if (body[0].x - 0 > 780 - body[0].x) {
                            direction = 3;
                        } else {
                            direction = 4;
                        }
                    }
                } else if (num == -5) {
                    body.clear();
                    for (int i = 0; i < sizelen; ++i) {
                        body.push_back(tempbody[i]);
                    }
                    if (body[0].x - 0 > 780 - body[0].x) {
                        direction = 3;
                    } else {
                        direction = 4;
                    }
                } else if (num == -6) {
                    body.clear();
                    for (int i = 0; i < sizelen; ++i) {
                        body.push_back(tempbody[i]);
                    }
                    if (body[0].y - 0 > 360 - body[0].y) {
                        direction = 1;
                    } else {
                        direction = 2;
                    }
                } else if (num == -7) {
                    body.clear();
                    for (int i = 0; i < sizelen; ++i) {
                        body.push_back(tempbody[i]);
                    }
                    if (body[0].x - 0 > 780 - body[0].x) {
                        direction = 3;
                    } else {
                        direction = 4;
                    }
                } else if (num == -8) {
                    body.clear();
                    for (int i = 0; i < sizelen; ++i) {
                        body.push_back(tempbody[i]);
                    }
                    if (body[0].x - 0 > 780 - body[0].x) {
                        direction = 3;
                    } else {
                        direction = 4;
                    }
                } else if (num == -9) {
                    body.clear();
                    for (int i = 0; i < sizelen; ++i) {
                        body.push_back(tempbody[i]);
                    }
                    if (body[0].y - 220 > 580 - body[0].y) {
                        direction = 1;
                    } else {
                        direction = 2;
                    }
                } else if (num == -10) {
                    body.clear();
                    for (int i = 0; i < sizelen; ++i) {
                        body.push_back(tempbody[i]);
                    }
                    if (body[0].x - 0 > 780 - body[0].x) {
                        direction = 3;
                    } else {
                        direction = 4;
                    }
                }
                blood--;
                alive = true;
            }
		    }

        bool check(int &num) {
            Posn shead = body[0];
            bool exist = false;
            for (int i = 1; i < body.size(); i++) {
                if (shead.x == body[i].x && shead.y == body[i].y) {
                    exist = true;
                    num = i;
                    break;
                }
            }
            if (exist) {
                return false;
            } else if (shead.x < 20 || shead.x >= 780 || shead.y < 20 || shead.y >= 580) {
                if (shead.x < 20) num = -1; // leftwall
                if (shead.x >= 780) num = -2; // rightwall
                if (shead.y < 20) num = -3; // upwall
                if (shead.y >= 580) num = -4; // downwall
                return false;
            }
            if (!obstacle.notonob(shead.x, shead.y)) {
                int templevel = obstacle.getlevel();
                if (templevel == 1) {
                    if (shead.y == 180 && (shead.x >= 20 && shead.x <= 600) && direction == 2) { //
                        num = -5;
                    } else if ((shead.y == 180 || shead.y == 200) && shead.x == 600 && direction == 3) {
                        num = -6;
                    } else if (shead.y == 180 && (shead.x >= 20 && shead.x <= 600) && direction == 1) {
                        num = -7;
                    } else if (shead.y == 380 && (shead.x >= 180 && shead.x <= 760) && direction == 2) {
                        num = -8;
                    } else if ((shead.y == 380 || shead.y == 400) && shead.x == 180 && direction == 4) {
                        num = -9;
                    } else {
                        num = -10;
                    }
                }
                return false;
            }
            return true;
        }

		    int getX() {
			      return x;
		    }

		    int getY() {
		  	    return y;
		    }

        vector<Posn> getBody() {
            return body;
        }

        bool checkalive() {
            return alive;
        }

        /*
         * ** ADD YOUR LOGIC **
         * Use these placeholder methods as guidance for implementing the snake behaviour.
         * You do not have to use these methods, feel free to implement your own.
         */
        void didEatFruit() {
            fruit = true;
        }

        void changedir(char c) {
            if (c == 'w') {
                if (direction != 2) direction = 1;
            } else if (c == 's') {
                if (direction != 1) direction = 2;
            } else if (c == 'a') {
                if (direction != 4) direction = 3;
            } else if (c == 'd') {
                if (direction != 3) direction = 4;
            }
        }

        void incblood () {
            ++blood;
        }

        void regen() {
            body.clear();
            x = 40;
            y = 500;
            blockSize = 20;
            Posn temp;
            temp.x = x;
            temp.y = y;
            body.push_back(temp);
            temp.x = x - 20;
            body.push_back(temp);
            alive = true;
            direction = 4;
            fruit = false;
            blood = 5;
        }

		Snake(int x, int y, int s = 20): x(x), y(y) {
        speed = s;
        blockSize = 20;
        Posn temp;
        temp.x = x;
        temp.y = y;
        body.push_back(temp);
        temp.x = x - 20;
        body.push_back(temp);
        alive = true;
        direction = 4;
        fruit = false;
        blood = 5;
		}

    int getBlood() {return blood;}


	private:
		int x;
		int y;
    int speed;
		int blockSize;
    vector<Posn> body;
    bool alive;
    int direction; // 1 = up, 2 = down, 3 = left, 4 = right
    bool fruit;
    int blood;
};

Snake snake(40, 560);

class Info : public Displayable {
    public:
        virtual void paint(XInfo &xinfo) {

            if (pause) {
                XSetForeground(xinfo.display, xinfo.gc[0], xinfo.colours[1]);
                XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0],
                300, 200, 200, 15);
                XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0],
                300, 200, 15, 200);
                XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0],
                485, 200, 15, 200);
                XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0],
                300, 385, 200, 15);

                XSetForeground(xinfo.display, xinfo.gc[0], xinfo.colours[6]);
                XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0],
                360, 240, 15, 120);
                XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0],
                420, 240, 15, 120);
            }

            // draw the wall
            XSetForeground(xinfo.display, xinfo.gc[0], xinfo.colours[1]);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0],
            0, 0, 800, 20);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0],
            0, 0, 20, 600);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0],
            780, 0, 20, 600);
            XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0],
            0, 580, 800, 5);

            XDrawString(xinfo.display, xinfo.window, xinfo.gc[0],  80, 595, "Life:", 5);
            int extrablood = snake.getBlood();
            if (obstacle.getlevel() != 2) {
                XSetForeground(xinfo.display, xinfo.gc[0], xinfo.colours[5]);
                for (int i = 0; i < extrablood; ++i) {
                    XSetForeground(xinfo.display, xinfo.gc[0], xinfo.colours[6]);
                    XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], 140 + 10 * i, 587, 10, 10);
                    XSetForeground(xinfo.display, xinfo.gc[0], xinfo.colours[1]);
                    XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0],
                    140 + 10 * i, 587, 10, 2);
                    XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0],
                    140 + 10 * i, 587, 2, 10);
                    XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0],
                    148 + 10 * i, 587, 2, 10);
                    XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0],
                    140 + 10 * i, 595, 10, 2);
                }
            } else {
                XSetForeground(xinfo.display, xinfo.gc[0], xinfo.colours[6]);
                XDrawString(xinfo.display, xinfo.window, xinfo.gc[0],  130, 595, "ONLY ONE LIFE!", 14);
            }

            XSetForeground(xinfo.display, xinfo.gc[0], xinfo.colours[1]);
            const char * lev = to_string(obstacle.getlevel()).c_str();
            const char * sco = to_string(score).c_str();
            const char * fp = to_string(fps).c_str();
            const char * spe = to_string(speed).c_str();


            XDrawString(xinfo.display, xinfo.window, xinfo.gc[0],  400, 595, "Level:", 6);
            XDrawString(xinfo.display, xinfo.window, xinfo.gc[0],  450, 595, sco, to_string(obstacle.getlevel()).length());

            XDrawString(xinfo.display, xinfo.window, xinfo.gc[0],  500, 595, "Score:", 6);
            XDrawString(xinfo.display, xinfo.window, xinfo.gc[0],  550, 595, sco, to_string(score).length());

            XDrawString(xinfo.display, xinfo.window, xinfo.gc[0],  600, 595, "FPS:", 4);
            XDrawString(xinfo.display, xinfo.window, xinfo.gc[0],  650, 595, fp, to_string(fps).length());

            XDrawString(xinfo.display, xinfo.window, xinfo.gc[0],  700, 595, "Speed:", 6);
            XDrawString(xinfo.display, xinfo.window, xinfo.gc[0],  750, 595, spe, to_string(speed).length());
        }

        Info (int fps = 30, int speed = 5, int score = 0, bool pause = false): fps(fps), speed(speed), score(score),
            pause{pause} {}

        void regen() {
            pause = false;
            tempscore = 0;
        }

        void incscore() {
           ++score;
          ++tempscore;
        }

        int gettempS() {
            return tempscore;
        }

        int getScore() {
            return score;
        }

        int setScore(int n) {
            score = n;
        }

        void setPause(bool p) {pause = p;}

        void setSpeed(int s) {speed = s;}

        void setFps(int f) {fps = f;}

        int getfps() {return fps;}
        int getspeed() {return speed;}


    private:
        int fps;
        int speed;
        int tempscore;
        int score;
        bool pause;

};

class Fruit : public Displayable {
	public:
		virtual void paint(XInfo &xinfo) {
      XSetForeground(xinfo.display, xinfo.gc[0], xinfo.colours[8]);
			XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], x, y, 20, 20);

      XSetForeground(xinfo.display, xinfo.gc[0], xinfo.colours[1]);

      XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], x, y, 2, 20);
      XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], x, y, 20, 2);
      XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], x + 18, y, 2, 20);
      XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], x, y + 18, 20, 2);
    }

        Fruit() {
            // ** ADD YOUR LOGIC **
            // generate the x and y value for the fruit
            genfruit();
        }

        void genfruit(int sx = 1000, int sy = 1000) {
            while (1) {
                x = rand() % 40 * 20;
                y = rand() % 30 * 20;
                Posn nfruit;
                nfruit.x = x;
                nfruit.y = y;
                vector <Posn> snakebody = snake.getBody();
                bool exist = true;
                for (int i = 0; i < snakebody.size(); i++) {
                    if (x == snakebody[i].x && y == snakebody[i].y) {
                        exist = false;
                        break;
                    }
                }
                if( x < 20 || x >= 780 || y < 20 || y >= 580) {
                    exist = false;
                }
                if (!obstacle.notonob(x, y)) exist = false;
                if (sx == x || sy == y) exist = false;
                if (exist) {
                    if (times == 6) times = 1;
                    break;
                }
            }
        }

        void regen() {
            times = 0;
            genfruit();
        }

        int getX() {
            return x;
        }

        int getY() {
            return y;
        }

        int getTimes() { return times;}

        void inctimes() {times++;}

        void settimes(int i) {times = i;}





        // ** ADD YOUR LOGIC **
        /*
         * The fruit needs to be re-generated at new location every time a snake eats it. See the assignment webpage for more details.
         */



    private:
        int x;
        int y;
        int times;
};





class Special : public Displayable {
public:
  virtual void paint(XInfo &xinfo) {
    if (obstacle.getlevel() == 2) return;
    XSetForeground(xinfo.display, xinfo.gc[0], xinfo.colours[6]);
    XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], x, y, 20, 20);

    XSetForeground(xinfo.display, xinfo.gc[0], xinfo.colours[1]);

    XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], x, y, 2, 20);
    XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], x, y, 20, 2);
    XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], x + 18, y, 2, 20);
    XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], x, y + 18, 20, 2);
  }

    Special () { genspecial();}

    void genspecial(int fx = 1000, int fy = 1000) {
      while (1) {
          x = rand() % 40 * 20;
          y = rand() % 30 * 20;
          Posn temp;
          temp.x = x;
          temp.y = y;
          vector <Posn> snakebody = snake.getBody();
          bool exist = true;
          for (int i = 0; i < snakebody.size(); i++) {
              if (x == snakebody[i].x && y == snakebody[i].y) {
                  exist = false;
                  break;
              }
          }
          if( x < 20 || x >= 780 || y < 20 || y >= 580) {
              exist = false;
          }
          if (!obstacle.notonob(x, y)) exist = false;
          if (x == fx || y == fy) exist = false;
          if (exist) {
              break;
          }
      }
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    void setexist(bool exi) {
        exist = exi;
    }

    bool getexist() {
        return exist;
    }

    void remtemp() {
        x = 1000;
        y = 1000;
        exist = false;
    }

private:
    int x;
    int y;
    bool exist;
};

list<Displayable *> dList;           // list of Displayables
Fruit fruit;
Special special;
Info info;


/*
 * Initialize X and create a window
 */
void initX(int argc, char *argv[], XInfo &xInfo) {
	XSizeHints hints;
	unsigned long white, black;

   /*
	* Display opening uses the DISPLAY	environment variable.
	* It can go wrong if DISPLAY isn't set, or you don't have permission.
	*/
	xInfo.display = XOpenDisplay( "" );
	if ( !xInfo.display )	{
		error( "Can't open display." );
	}

   /*
	* Find out some things about the display you're using.
	*/
	xInfo.screen = DefaultScreen( xInfo.display );

	white = XWhitePixel( xInfo.display, xInfo.screen );
	black = XBlackPixel( xInfo.display, xInfo.screen );

	hints.x = 100;
	hints.y = 100;
	hints.width = 800;
	hints.height = 600;
	hints.flags = PPosition | PSize;

	xInfo.window = XCreateSimpleWindow(
		xInfo.display,				// display where window appears
		DefaultRootWindow( xInfo.display ), // window's parent in window tree
		hints.x, hints.y,			// upper left corner location
		hints.width, hints.height,	// size of the window
		Border,						// width of window's border
		black,						// window border colour
		white );					// window background colour

	XSetStandardProperties(
		xInfo.display,		// display containing the window
		xInfo.window,		// window whose properties are set
		"animation",		// window's title
		"Animate",			// icon's title
		None,				// pixmap for the icon
		argv, argc,			// applications command line args
		&hints );			// size hints for the window



// set up colors
    Colormap c;
    XColor xcolour;

    char color[10][10]={"white", "black", "yellow", "green", "blue", "grey", "red", "magenta", "orange", "brown"};
    c = DefaultColormap(xInfo.display, DefaultScreen(xInfo.display));
    for(int i = 0; i < 10; i++) {
            if (!XParseColor(xInfo.display,c,color[i], &xcolour)) {
                cerr << color[i] << endl;
            }
            if (!XAllocColor(xInfo.display,c, &xcolour)) {
                cerr << color[i] << endl;
            }
        xInfo.colours[i] = xcolour.pixel;
    }


	/*
	 * Create Graphics Contexts
	 */
	int i = 0;
	xInfo.gc[i] = XCreateGC(xInfo.display, xInfo.window, 0, 0);
	XSetForeground(xInfo.display, xInfo.gc[i], BlackPixel(xInfo.display, xInfo.screen));
	XSetBackground(xInfo.display, xInfo.gc[i], WhitePixel(xInfo.display, xInfo.screen));
	XSetFillStyle(xInfo.display, xInfo.gc[i], FillSolid);
	XSetLineAttributes(xInfo.display, xInfo.gc[i],
	                     1, LineSolid, CapButt, JoinRound);

	XSelectInput(xInfo.display, xInfo.window,
		ButtonPressMask | KeyPressMask |
		PointerMotionMask |
		EnterWindowMask | LeaveWindowMask |
		StructureNotifyMask);  // for resize events

	/*
	 * Put the window on the screen.
	 */
	XMapRaised( xInfo.display, xInfo.window );
	XFlush(xInfo.display);
}

/*
 * Function to repaint a display list
 */
void repaint( XInfo &xinfo) {
	list<Displayable *>::const_iterator begin = dList.begin();
	list<Displayable *>::const_iterator end = dList.end();

	XClearWindow( xinfo.display, xinfo.window );

	// get height and width of window (might have changed since last repaint)

	XWindowAttributes windowInfo;
	XGetWindowAttributes(xinfo.display, xinfo.window, &windowInfo);
	unsigned int height = windowInfo.height;
	unsigned int width = windowInfo.width;

	// big black rectangle to clear background

	// draw display list
	while( begin != end ) {
		Displayable *d = *begin;
		d->paint(xinfo);
		begin++;
	}
	XFlush( xinfo.display );
}

void handleKeyPress(XInfo &xinfo, XEvent &event, bool &pause, int &pausetime, bool &restart, bool &end) {
	KeySym key;
	char text[BufferSize];

	/*
	 * Exit when 'q' is typed.
	 * This is a simplified approach that does NOT use localization.
	 */
	int i = XLookupString(
		(XKeyEvent *)&event, 	// the keyboard event
		text, 					// buffer when text will be written
		BufferSize, 			// size of the text buffer
		&key, 					// workstation-independent key symbol
		NULL );					// pointer to a composeStatus structure (unused)
	if ( i == 1) {
		printf("Got key press -- %c\n", text[0]);
		if (text[0] == 'q') {
			  error("Terminating normally.");
		} else if (text[0] == 'w' || text[0] == 's' || text[0] == 'a' || text[0] == 'd') {
        snake.changedir(text[0]);
    } else if (text[0] == 'r') { // restart
        restart = true;
        end = false;
    } else if (text[0] == 'p') { // pause
        pausetime = 1 - pausetime;
        if (pausetime == 0) {
            pause = true;
        } else {
            pause = false;
        }
    }
	}
}

unsigned long now() {
	timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

void handleAnimation(XInfo &xinfo, int inside) {
    /*
     * ADD YOUR OWN LOGIC
     * This method handles animation for different objects on the screen and readies the next frame before the screen is re-painted.
     */
  //cout << "now: " << now() << endl;
 	snake.move(xinfo);

  Posn head = snake.getBody()[0];
  if (fruit.getX() == head.x && fruit.getY() == head.y) {
      if (!special.getexist()) {
          fruit.inctimes();
          fruit.genfruit();
      } else {
          fruit.settimes(0);
          fruit.genfruit(special.getX(), special.getY());
      }
      snake.didEatFruit();
      info.incscore();
  }

  if (special.getX() == head.x && special.getY() == head.y) {
      special.setexist(false);
      special.remtemp();
      snake.incblood();
  }

}

void screenclean(XInfo &xinfo, XEvent &event) {
    XClearWindow(xinfo.display, xinfo.window);
    XSetForeground(xinfo.display, xinfo.gc[0], xinfo.colours[1]);
    int s = info.getScore();
    const char * sco = to_string(s).c_str();
    XDrawString(xinfo.display, xinfo.window, xinfo.gc[0],  370, 280, "GAME OVER!", 10);
    XDrawString(xinfo.display, xinfo.window, xinfo.gc[0],  370, 300, "Score:", 6);
    XDrawString(xinfo.display, xinfo.window, xinfo.gc[0],  420, 300, sco, to_string(s).length());
    XDrawString(xinfo.display, xinfo.window, xinfo.gc[0],  290, 320, "Press Q to quit or Press R to restart.", 38);
}

// get microseconds

////////////////////////////////////////////////////////////////////////////////
void eventLoop(XInfo &xinfo) {
	// Add stuff to paint to the display list
    dList.push_front(&info);
	  dList.push_front(&snake);
    dList.push_front(&fruit);
    dList.push_front(&special);
    dList.push_front(&obstacle);
    special.remtemp();

	  XEvent event;
	  unsigned long lastRepaint = 0;
    unsigned long lastMove = 0;

	  int inside = 0;

    bool restart = false;

    bool pause = false;
    int pausetime = 1;

    bool end = false;

  	while( true ) {
		/*
		 * This is NOT a performant event loop!
		 * It needs help!
		 */

	    if (XPending(xinfo.display) > 0) {
		   	XNextEvent( xinfo.display, &event );
		  	//cout << "event.type=" << event.type << "\n";
		  	switch( event.type ) {
		  		case KeyPress:
		  			handleKeyPress(xinfo, event, pause, pausetime, restart, end);
		  			break;
		  		case EnterNotify:
	  				inside = 1;
	  				break;
	  			case LeaveNotify:
	  				inside = 0;
	  				break;
	  		}
	  	}

      if (end) {
         continue;
      }

      info.setPause(pause);

      if (fruit.getTimes() == 5 && !special.getexist()) {
           fruit.settimes(0);
           special.genspecial(fruit.getX(), fruit.getY());
           special.setexist(true);
      }


      if (restart || (info.gettempS() == 10 && obstacle.getlevel() != 2)) {
          if (info.gettempS() == 10) {
              obstacle.levelinc();
          } else {
              obstacle.setlevel(0);
              info.setScore(0);
          }
          snake.regen();
          fruit.regen();
          info.regen();
          special.remtemp();
          restart = false;
          pause = false;
          pausetime = 1;
          continue;
      }

      unsigned long endfps = now();
      unsigned long endmove = now();

        if (!pause) {
            if (endmove - lastMove > 500000 / info.getspeed()) {
               handleAnimation(xinfo, inside);
               lastMove = now();
            }
        }

        if (endfps - lastRepaint > 1000000 / info.getfps()) {
          repaint(xinfo);
          lastRepaint = now();
        }


      if (XPending(xinfo.display) == 0) {
          usleep(1000000/info.getfps() - (endfps - lastRepaint));
      }

      if (!snake.checkalive()) {
          screenclean(xinfo, event);
          end = true;
      }
	}
}
////////////////////////////////////////////////////////////////////////////////

/*
 * Start executing here.
 *	 First initialize window.
 *	 Next loop responding to events.
 *	 Exit forcing window manager to clean up - cheesy, but easy.
 */
int main ( int argc, char *argv[] ) {
	XInfo xInfo;


  if (argc == 2) {
      int f = stoi(argv[1]);
      info.setFps(f);
  }
  if(argc == 3) {
  int f = stoi(argv[1]);
  int s = stoi(argv[2]);
  info.setFps(f);
  info.setSpeed(s);
  }

	initX(argc, argv, xInfo);
	eventLoop(xInfo);
	XCloseDisplay(xInfo.display);
}


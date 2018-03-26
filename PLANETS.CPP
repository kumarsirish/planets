/*      Planets -- A Project By Shubham Kumar
 *              Class : X11 'A'
 *              Class Roll number: 26
 */

#include <graphics.h>
#include <dos.h>
#include <iostream.h>
#include <ctype.h>
#include <stdio.h>
#include <fstream.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <time.h>

//Put all planet's text files at the below location.
char path[] = "C:\\TURBOC3\\Projects\\";
char bgi_path[] = "C:\\TURBOC3\\BGI";

//Global declarations and definitions
int maxx, maxy, fontheight = 11; //screen sizes and default font height
int correct = 0, wrong = 0; // count of right and correct answers
float total = 0; // count of total questions
char new_planet_name[30] = ""; //name of new planet initialized to empty string
void * buff; //buffer to store the image
int x = 7, y = 10; // Start text coordinates
char file_ext[] = ".dat"; //File extension

//Common global functions
//Start the graphics mode
void start_graphics_mode() {
    int gdriver = DETECT, gmode, errorcode;
    initgraph( & gdriver, & gmode, bgi_path);
    maxx = getmaxx();
    maxy = getmaxy();
}

//Takes planet's color in string format and returns the equivalent integrer for it
int get_planet_color(char color[]) {
    if (strcmp("RED", color) == 0)
        return RED;
    else if (strcmp("GREEN", color) == 0)
        return GREEN;
    else if (strcmp("BLUE", color) == 0)
        return BLUE;
    else if (strcmp("YELLOW", color) == 0)
        return YELLOW;
    else if (strcmp("BROWN", color) == 0)
        return BROWN;
    else if (strcmp("MAGENTA", color) == 0)
        return MAGENTA;
    return WHITE;
}

//Draws the ball on screen
void draw_ball(int color) {
    int x = 340;
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    circle(x, 40, 10);
    floodfill(x, 40, color);

    //Allocate the size of buffer to store image
    buff = malloc(imagesize(30, 30, 50, 50));
    getimage(x - 10, 30, x + 10, 50, buff);
    putimage(x - 10, 30, buff, XOR_PUT);
}

/*Moves the ball from top of the screen to the bottom of the screen
 * based on the gravity of the planet.
 Input: Position of the ball at x as INT
	Color of the ball as INT
	Delay in fall : INT
*/
void animate_ball(int x, int color, int t) {

    int XCoord = x, YCoord = 0;
    int dy = 5;

    draw_ball(color);

    while (1) {
        putimage(XCoord, YCoord, buff, XOR_PUT);
        //delay(40);
        delay((40 / 6) * t);
        putimage(XCoord, YCoord, buff, XOR_PUT);

        YCoord += dy;
        if (YCoord >= getmaxy() - 32) {
            break;
        }

    }

}

//Draws a rectangle in text mode
void draw_rectangle(int xmin, int ymin, int xmax, int ymax) {
    int i = 0;

    for (i = xmin; i < xmax; i++) {
        gotoxy(i, ymin);
        cprintf("=");
        gotoxy(i, ymax);
        cprintf("=");
    }
    for (i = ymin; i < ymax; i++) {
        gotoxy(xmin, i);
        cprintf("|");
        gotoxy(xmax, i);
        cprintf("|");

    }

}

// Draws the quiz banner on the top
void draw_quiz_banner() {
        gotoxy(20, 5);
        cprintf("WELCOME TO THE QUIZ");
        draw_rectangle(1, 1, 80, 25);

    }
    //CLASS definitions

//CLASS: Planets

class planets {
    private:
        float radius;
    float mass;
    float distfrmsun;
    float gravity;
    float atmosphere;
    char colour[10];
    char filename[100]; // file in which planet's information is stored
    char name[50]; //planets name

    public:
        float retrad() {
            return radius;
        }
    float retmas() {
        return mass;
    }

    float retdis() {
        return distfrmsun;
    }

    //Set the file name for a given planet
    void setfilename(char f[]) {
        strcpy(filename, f);
    }

    //Derives planet file name from its name
    char * getfilename() {
        strcpy(filename, path);
        strcat(filename, getplanetname());
        strcat(filename, file_ext);
        return filename;
    }

    //Set planet name
    void setplanetname(char f[]) {
        strcpy(name, f);
        read_planet_attributes();
    }

    //Get planet name
    char * getplanetname() {
        return name;
    }

    //Set planet color
    int set_planet_color(char col[]) {
        return get_planet_color(col);
    }

    //Draw planet in graphics mode
    void drawplanet() {

        //Draw stars
        for (int i = 0; i <= 500; i++) {
            putpixel(rand() % maxx, rand() % maxy, 15);
        }

        //Draw planet
        int x = 3 * (getmaxx() / 4);
        int y = getmaxy() / 2;
        setcolor(getmaxcolor());
        double screenrad;
        screenrad = radius / (500);
        circle(x, y, screenrad);
        setfillstyle(1, set_planet_color(colour));
        fillellipse(x, y, screenrad, screenrad);

    }

    //Enhancement functions for future
    void display_his();
    void display_triv();

    //Gets planet's properties from the binary file
    void read_planet_attributes() {
        fstream file;
        char errorstring[100];
        file.open(getfilename(), ios:: in , ios::binary);

        if (file.fail()) {
            sprintf(errorstring, "Error: Missing File %s from %s\n", getfilename(), path);
            perror(errorstring);
            getch();
            exit(1);
        }
        file >> radius;
        file >> mass;
        file >> gravity;
        file >> atmosphere;
        file >> distfrmsun;
        file >> colour;

    }

    //Calculates time to fall for an object
    float time_to_fall() {
        int distance = 1000; //meters
        float acceleration = gravity; // meters per sec^2
        float time = 0; //seconds

        time = sqrt(2 * distance / acceleration);
        return time;

    }

    //Displays the planet details in graphics mode
    void graphics_output() {
            // fstream file2;
            char outputstring[128];

            read_planet_attributes();
            start_graphics_mode();

            int x = 2, y = maxy / 2;
            rectangle(0, 0, maxx, maxy);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 8);
            outtextxy(x, 10, getplanetname());
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
            sprintf(outputstring, "RADIUS OF PLANET : %.0f kms", radius);
            outtextxy(x, y, outputstring);
            sprintf(outputstring, "MASS OF PLANET : %.0f 10^24 kgs", mass);
            outtextxy(x, y + fontheight, outputstring);
            sprintf(outputstring, "GRAVITY OF PLANET : %.0f m/s^2", gravity);
            outtextxy(x, y + fontheight * 2, outputstring);
            sprintf(outputstring, "ATMOSPHERE OF PLANET : %.0f kms", atmosphere);
            outtextxy(x, y + fontheight * 3, outputstring);
            sprintf(outputstring, "DISTANCE FROM SUN : %.0f million kms", distfrmsun);
            outtextxy(x, y + fontheight * 4, outputstring);
            sprintf(outputstring, "Color : %s", colour);
            outtextxy(x, y + fontheight * 5, outputstring);

            setcolor(YELLOW);
            sprintf(outputstring, "Height: 1000m, Gravity: %.2fm/s^2, Time taken: %.2fs", gravity, time_to_fall());
            outtextxy(maxx / 2 - 120, maxy - 10, outputstring);
            drawplanet();
            animate_ball((maxx / 3 + 50), RED, time_to_fall());
            outtextxy(x, maxy - 20, "Press any key to continue ...");
            getch();
            setcolor(getmaxcolor());
            closegraph();
            restorecrtmode();
        }
        //Enhancement: Modify a Planet for future
    void modify();

    //Create a Planet
    void create() {
            int x = 10, y = 10;
            char errorstring[128];
            char filename[128];
            clrscr();

            draw_rectangle(1, 1, 80, 25);

            gotoxy(x, y - 1);
            cprintf("NAME YOUR PLANET (8 chars) : ");
            cin >> new_planet_name;

            gotoxy(x, y);
            cprintf("ENTER RADIUS OF PLANET (kms): ");
            cin >> radius;

            gotoxy(x, y + 1);
            cprintf("ENTER MASS OF PLANET (million kgs): ");
            cin >> mass;

            gotoxy(x, y + 2);
            cprintf("ENTER GRAVITY ON PLANET (m/s^2) : ");
            cin >> gravity;

            gotoxy(x, y + 3);
            cprintf("ENTER THE LENGTH OF ATMOSPHERE ON PLANET (kms): ");
            cin >> atmosphere;

            gotoxy(x, y + 4);
            cprintf("ENTER DISTANCE FROM SUN (million kms): ");
            cin >> distfrmsun;

            gotoxy(x, y + 5);
            cprintf("ENTER COLOUR OF THE PLANET (RED, GREEN, BLUE, MAGENTA): ");
            cin >> colour;

            strcpy(filename, path);
            strcat(filename, new_planet_name);
            strcat(filename, file_ext);
            ofstream file(filename, ios::out, ios::binary);
            if (file.fail()) {
                sprintf(errorstring, "Error: Unable to open file %s\n", filename);
                perror(errorstring);
                getch();
                exit(1);
            }
            file << radius << endl;
            file << mass << endl;
            file << gravity << endl;
            file << atmosphere << endl;
            file << distfrmsun << endl;
            file << colour << endl;
            file.close();

            gotoxy(x, y + 7);
            cprintf("Congratulations !!! New ninth planet is created.");
            gotoxy(x, y + 8);
            cprintf("Select option (1) from main menu to view it.");
            gotoxy(x, y + 10);
            cprintf("Press any key for main menu ...");

        }
        //Delete a planet
    void delete_planet(char filename[]) {
        int x = 10, y = 10;
        char errorstring[128];
        char choice;

        clrscr();

        draw_rectangle(1, 1, 80, 25);

        sprintf(errorstring, "Are you sure to delete the planet %s (Y/N): ", new_planet_name);
        gotoxy(x - 5, y - 1);
        cprintf(errorstring);
        cin >> choice;
        if (choice == 'y') {
            if (remove(filename) != -1) {
                gotoxy(x - 5, y + 4);
                cprintf("Congratulations !!! Planet is deleted.");
                cprintf("Press any key for main menu ...");

            } else {
                gotoxy(x, y + 4);
                cprintf("Sorry, you are not God ! Planet cannot be deleted");
                getch();
            }
        }
    }
};

//Intro Screen
void intro_screen(void) {

    start_graphics_mode();
    rectangle(0, 0, maxx, maxy);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 8);
    for (int i = 0; i <= 500; i++) {
        putpixel(rand() % maxx, rand() % maxy, 15);
    }
    outtextxy(x + 160, 100, "PLANET ");
    outtextxy(x + 70, 170, "INFORMATION");
    outtextxy(x + 160, 240, "SYSTEM");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(x + 400, 400, " -BY SHUBHAM KUMAR-12 A");
    outtextxy(x + 433, 420, " ROLL NO:26");
    outtextxy(x + 430, 440, " NATIONAL PUBLIC SCHOOL");
    getch();
    closegraph();
}

// Displys planets menu.
void display_planet_menu(void) {

    int x = 10, y = 10;

    draw_rectangle(1, 1, 80, 25);
    gotoxy(x, y);
    cprintf("CHOOSE PLANETS");
    gotoxy(x, y + 1);
    cprintf("1. MERCURY");
    gotoxy(x, y + 2);
    cprintf("2. VENUS");
    gotoxy(x, y + 3);
    cprintf("3. EARTH");
    gotoxy(x, y + 4);
    cprintf("4. MARS");
    gotoxy(x, y + 5);
    cprintf("5. JUPITER");
    gotoxy(x, y + 6);
    cprintf("6. SATURN");
    gotoxy(x, y + 7);
    cprintf("7. URANUS");
    gotoxy(x, y + 8);
    cprintf("8. NEPTUNE");
    gotoxy(x, y + 10);
    if (strcmp(new_planet_name, "") != 0) {
        cprintf("9. %s <-- New Planet", new_planet_name);
        gotoxy(x, y + 12);
    }
    cprintf("Enter your choice : ");
}

//CLASS: question
class question {
    private:
        char ques[400];
    char ansuser; //answer given by user
    char ansactual[5]; //actual answer
    char object_name[10];

    public:
        void getans() {

            gotoxy(x, y + 7);
            cprintf("Enter your answer A, B, C, D: ");
            cin >> ansuser;
        }
    void setobjname(char r[]) {
        strcpy(object_name, r);
    }

    //Reads questions from the binary file
    void readques() {
        fstream file1;
        char filename[50];
        char option1[50], option2[50], option3[50], option4[50];
        strcpy(filename, path);
        strcat(filename, "QUEST");
        strcat(filename, object_name);
        strcat(filename, file_ext);
        file1.open(filename, ios:: in , ios::binary);

        //read question
        file1.getline(ques, sizeof(ques), '.');
        gotoxy(x, y);
        cprintf(ques);

        //read options
        file1.getline(option1, sizeof(option1), '.');
        file1.getline(option2, sizeof(option2), '.');
        file1.getline(option3, sizeof(option3), '.');
        file1.getline(option4, sizeof(option4), '.');

        //print options
        gotoxy(x, y + 1);
        cprintf(option1);
        gotoxy(x, y + 2);
        cprintf(option2);
        gotoxy(x, y + 3);
        cprintf(option3);
        gotoxy(x, y + 4);
        cprintf(option4);

        //get actual answer
        file1.get(ansactual, sizeof(ansactual), '#');

    }

    //Checks the answer
    void checkans() {
        gotoxy(x, y + 8);
        if (ansactual[1] == toupper(ansuser)) {
            cprintf("Correct Answer !!!.");
            correct++;
        } else {
            cprintf("Wrong Answer !!!");
            wrong++;
        }
        gotoxy(x, y + 9);
        cprintf("Press 'e' to exit form quiz or any other key to continue ...");

    }

};

// Function to display quiz questions, compare answers
void take_quiz() {
        question q[16];
        char choice;

        //setting object names which are nothing but objects of question class
        q[1].setobjname("1");
        q[2].setobjname("2");
        q[3].setobjname("3");
        q[4].setobjname("4");
        q[5].setobjname("5");
        q[6].setobjname("6");
        q[7].setobjname("7");
        q[8].setobjname("8");
        q[9].setobjname("9");
        q[10].setobjname("10");
        q[11].setobjname("11");
        q[12].setobjname("12");
        q[13].setobjname("13");
        q[14].setobjname("14");
        q[15].setobjname("15");

        clrscr();
        randomize(); //randomly selects questions
        //int k = 0;
        for (int i = 1; i <= 15; i++) {
            clrscr();
            draw_quiz_banner();
            // k = rand() % 15;
            q[i].readques();
            q[i].getans();
            q[i].checkans();

            choice = getch();
            if (choice == 'e' || choice == 'E') break;
        }
        clrscr();
        draw_quiz_banner();
        gotoxy(x, y);
        cprintf("TOTAL NO OF WRONG ANSWERS: %d", wrong);
        gotoxy(x, y + 1);
        cprintf("TOTAL NO OF CORRECT ANSWERS: %d", correct);
        total = ((correct * 100) / (correct + wrong));
        gotoxy(x, y + 2);
        cprintf("TOTAL SCORE IS : %2.2f%", total);
        gotoxy(x, y + 6);
        cprintf("Press any key for main menu ...");

    }
    //Initialize the planets at program start

planets venus, mars, earth, mercury, jupiter, uranus, saturn, neptune, newplanet;

void simulate_gravity_on_planets() {
    char outputstring[128];
    float time_to_fall = 6.0;
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

    //Draw stars
    for (int i = 0; i <= 500; i++) {
        putpixel(rand() % maxx, rand() % maxy, 15);
    }

    rectangle(0, 0, maxx, maxy);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(20, 20, "Falling object time ");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

    //Venus
    time_to_fall = venus.time_to_fall();
    sprintf(outputstring, "Venus:%0.2fs", time_to_fall);
    outtextxy(100, maxy - 50, outputstring);
    animate_ball(150, RED, time_to_fall);

    //Jupiter
    setcolor(WHITE);
    time_to_fall = jupiter.time_to_fall();
    sprintf(outputstring, "Jupiter:%0.2fs", time_to_fall);
    outtextxy(250, maxy - 50, outputstring);
    animate_ball(250, BROWN, time_to_fall);

    //Mars
    setcolor(WHITE);
    time_to_fall = mars.time_to_fall();
    sprintf(outputstring, "Mars:%0.2fs", time_to_fall);
    outtextxy(400, maxy - 50, outputstring);
    animate_ball(450, YELLOW, time_to_fall);

}

void admin_menu(void) {

        char admin_password[] = "welcome";
        char actual_password[10];
        char choice;
        char filename[150];

        clrscr();
        draw_rectangle(1, 1, 80, 25);
        gotoxy(10, 10);
        cprintf("Enter admin password: ");
        cin >> actual_password;
        gotoxy(10, 11);

        if (!strcmp(actual_password, admin_password)) {
            cprintf("Password matches");
        } else
            cprintf("Password does not match");

        clrscr();
        draw_rectangle(1, 1, 80, 25);
        gotoxy(10, 10);

        cprintf("ADMIN: WHAT DO YOU WISH TO DO??");
        gotoxy(10, 11);
        cprintf("1 : CREATE PLANETS");
        gotoxy(10, 12);
        cprintf("2 : DELETE PLANETs");
        gotoxy(10, 15);
        cprintf("0 : EXIT");
        gotoxy(10, 17);
        cprintf("Enter your choice: ");
        cin >> choice;

        if (choice == '1') {
            char name[12];
            newplanet.create();
            newplanet.setplanetname(new_planet_name);

        } else if (choice == '2') {

            
            gotoxy(10, 10);
            cprintf("Deleting planet : %s\n", new_planet_name);
            if (strcmp(new_planet_name, "")) {

                strcpy(filename, path);
                strcat(filename, new_planet_name);
                strcat(filename, file_ext);
                newplanet.delete_planet(filename);
                strcpy(new_planet_name, "");

            } else {
				clrscr();
                gotoxy(10, 11);
                cprintf("No planet to delete. First create a planet.");

            }
        }
        getch();

    }
    //Start the program
void main() {
    clrscr();
    mercury.setplanetname("MERCURY");
    venus.setplanetname("VENUS");
    earth.setplanetname("EARTH");
    mars.setplanetname("MARS");
    jupiter.setplanetname("JUPITER");
    saturn.setplanetname("SATURN");
    uranus.setplanetname("URANUS");
    neptune.setplanetname("NEPTUNE");

    int choice1, choice2;
    intro_screen();
    do {
        clrscr();
        draw_rectangle(1, 1, 80, 25);
        gotoxy(10, 10);
        cprintf("WHAT DO YOU WISH TO DO??");
        gotoxy(10, 11);
        cprintf("1 : INFORMATION ON PLANETS");
        gotoxy(10, 12);
        cprintf("2 : CREATE/DELETE MAN MADE PLANETs");
        gotoxy(10, 13);
        cprintf("3 : FALLING OBJECT ON DIFFERENT PLANETS");
        gotoxy(10, 14);
        cprintf("4 : QUIZ");
        gotoxy(10, 15);
        cprintf("0 : EXIT");
        gotoxy(10, 17);
        cprintf("Enter your choice: ");
        cin >> choice1;
        switch (choice1) {
        case 1: //Display information about planets
            clrscr();
            display_planet_menu();
            cin >> choice2;
            if (choice2 == 2) {
                venus.graphics_output();
                break;
            } else if (choice2 == 3) {
                earth.graphics_output();
                break;
            } else if (choice2 == 1) {
                mercury.graphics_output();
                break;
            } else if (choice2 == 4) {
                mars.graphics_output();
                break;
            } else if (choice2 == 5) {
                jupiter.graphics_output();
                break;
            } else if (choice2 == 6) {
                saturn.graphics_output();
                break;
            } else if (choice2 == 7) {
                uranus.graphics_output();
                break;
            } else if (choice2 == 8) {
                neptune.graphics_output();
                break;
            } else if (choice2 == 9) {
                newplanet.graphics_output();
                break;
            } else
                cout << "incorrect input";
            getch();
            break;

        case 2: //Create, Delete a new planet
            admin_menu();
            break;
        case 3: //Animate falling objects on various planets
            cout << "Falling objects from a height on various planets";
            start_graphics_mode();
            simulate_gravity_on_planets();
            setcolor(YELLOW);
            outtextxy(150, maxy / 2, "Thats it! Press Any Key for Main Menu ...");
            getch();
            closegraph();
            break;
        case 4: //Take Quiz
            take_quiz();
            getch();
            break;

        case 0: //Exits successfully
            exit(0);
        default:
            cout << "incorrect input";
            break;
        } //switch//

    }
    while (1); //Loop till user selects option "0"

}
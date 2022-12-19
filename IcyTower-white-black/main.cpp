#include<Windows.h>
#include<math.h>
#include<GL\glut.h>
bool fullScreen = true, gameover=false , stop;
bool keyStates[256];
int c1 = 0 , qc = 1;
float width ,height , sWidth , sHeight
	, r = 2 , cx , cy ,rx=0,ry=0,delrx = .3, delry = .3 ,delcx = .3, delcy = .3, xq,yq , delqx = 0.3 , delqy = 0.3,
	 PI = 22/7.0;


void draw();
void reshape(int,int);
void backGround();
void timer(int);


void keyboarddown(unsigned char  , int , int);
void keyboardup(unsigned char  , int , int);
void keySpecialdown(int,int,int);
void keySpecialup(int,int,int);


void mouse (int , int , int , int);


int main( int argc , char ** argv){
	// glut init
	glutInit(&argc , argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);
	
	glutCreateWindow("final");
	glutFullScreen();

	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	glutTimerFunc(0,timer,0);
	

	glutKeyboardFunc(keyboarddown);
	glutKeyboardUpFunc(keyboardup);
	glutSpecialFunc(keySpecialdown);
	glutSpecialUpFunc(keySpecialup);
//	glutMouseFunc(mouse);
	
	
	backGround();

	glutMainLoop();
}
void reshape(int w ,int h ){
	float ratio;
	if( h == 0 )
		h = 1;
	ratio = (float)w / h ;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if( w >= h ){
		gluOrtho2D(-10*ratio,10*ratio,-10,10);
		sWidth = 10*ratio ;
		sHeight = 10;
	}
	else{
		gluOrtho2D(-10,10,-10/ratio,10/ratio);
		sWidth = 10 ;
		sHeight = 10/ratio;
	}
	glMatrixMode(GL_MODELVIEW);
}
void backGround(){
	// color [0,1]
	glClearColor(0,.4,0,0);
}

void timer(int v){
	// repaint
	glutPostRedisplay();
	if(gameover != true){
		glutTimerFunc(1000/25,timer,0);
	}
	
	
//	cx = delcx;
	cy = delcy;
	
//	rx= delry;
	ry= delry;
	xq += delqx  ;
		//right					//left
	if( xq > sWidth-4 || xq < -sWidth+2 )
		delqx = -delqx;
	yq += delqy; 
	if( yq > sHeight-2 || yq < -sHeight)
		delqy = -delqy;
}

void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	

	glBegin(GL_QUADS);
	glColor3f(c1,0,0);
	//left
	glVertex2f(-18+cx , cy+1);
	glVertex2f(-16+cx , cy+1);
	glVertex2f(-16+cx , cy+4);
	glVertex2f(-18 , cy+4);
	glEnd();
	
	//right
	glBegin(GL_QUADS);
	glColor3f(c1,0,0);
	glVertex2f(18+rx , ry+1);
	glVertex2f(16+rx , ry+1);
	glVertex2f(16+rx , ry+4);
	glVertex2f(18+rx , ry+4);
	glEnd();
	
	// [$$$$$$$$$$$$$$$$$$$$$$$$$$$$$]
	// draw squar
	glColor3f(0,0,1);
	glBegin(GL_QUADS);
	glVertex2f(xq,yq);
	glVertex2f(xq+2,yq);
	glVertex2f(xq+2,yq+2);
	glVertex2f(xq,yq+2);
	glEnd();
	
	
	glutSwapBuffers();
}



void keyboarddown(unsigned char key , int x , int y ){

	

	if ( key == 'w' || key == 'W') // vertical [|]
		delry += .3;
	else if ( key == 's' || key == 'S') // vertical [|]
		delry -= .3;
	
		qc = !qc;
	if( key == 27) // exit game when press esc 
		exit(0);
}


void keyboardup(unsigned char key  , int x , int y ){
	keyStates[key] = false; // convert key status to false
}

// when you press a button this function run
void keySpecialdown(int key ,int x ,int y ){
	keyStates[key] = true;
 
	if ( key == GLUT_KEY_UP)
		delcy += .3;
	else if ( key == GLUT_KEY_DOWN)
		delcy -= .3;

	else if(key == GLUT_KEY_F1){
		fullScreen = !fullScreen;
		if(fullScreen)
			glutFullScreen();
		else{
				// change from full to half size
				glutReshapeWindow(width/2 , height/2);
				// make it on center of screen
				glutPositionWindow(width/2 -
					width/4, height/2 - height/4 );
			}
	}
}

// when you release a button this function run
void keySpecialup(int key,int x ,int y ){
	keyStates[key] = false; // convert keySpecial status to false
}


void mouse (int button , int state , int x , int y){
	
	// when press mouse left button && status is DOWN not release
	if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		stop = !stop; 
		if(!stop){
			delqx = .3;
			delqy = .3;
			qc = !qc; // change suar color
		}
		else{
			delqx = 0;
			delqy = 0;
			// each time move right why? +
		}
	}

}




/********************************************************************
 FILE: tile_1.cpp
 NAME: E. Mudrak
 DATE LAST MODIFIED: 2/8/2015
 DESCRIPTION:
	Uses array of coordinates to: 
		- Draw a tile of my design to screen, repeated so that window could be fit
		- Tessellate design across window
		- Utilizes SetVP() to control tile design
		- Draws tile design 'n' times as entered in the command line by the user,
			drawing 'n' tiles along each axis
		
 KEYS:  ESC to exit program

 Assumes all header files and shader files (vshader_tile.glsl, fshader_tile.glsl) 
 	are in the same directory
********************************************************************/

 #ifdef __APPLE__       
 #include <GLUT/glut.h>
 #else		       
 #include <GL/glut.h>         
 #endif

#include "Angel.h"  //Provides InitShader, vec4

//GLOBAL VARIABLES and CONSTANTS:
int num_tiles;
int window_width=800, window_height=800;
const int NUMVERTICES= 48;
bool wireframe = false;
bool filled = true;
GLuint vPosition, vColor;


//FUNCTIONS:
void init();									
void display();									
void keyboard(unsigned char key, int x, int y);	
void drawCube();
void SetVP(double leftx,double lefty,double rightx, double righty);				

int main(int argc, char** argv) 
{
  glutInit(&argc,argv); 
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(window_width,window_height);

  num_tiles = atoi(argv[1]); 		//convert the string argument to integer
  glutCreateWindow( argv[1] );	   //use the string version for window title

  glutInitWindowPosition(0,0);  
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);  
  init();
  glutMainLoop();

}
/////////////////////////////////////////////////////////////////////////////////

void display() 
{
  glClear(GL_COLOR_BUFFER_BIT); 

  // (L,B,R,T) using num_tiles, 'n' along each axis
  double vp1 = 0;
  double vp2 = 0;
  double newVp1 = 1.0 / num_tiles;
  double newVp2 = 1.0 / num_tiles;
	
  // Viewports incremented both until the the end of each axis, x and y 
  for (int i=0; i < num_tiles; i++) {
	for (int j=0; j < num_tiles; j++) {
		SetVP(vp1, vp2, vp1 + newVp1, vp2 + newVp2);
		vp1+=newVp1;
		drawCube();		
	}
	// First row is complete, set vp1 back to 0 to move up a row 
	vp1 = 0;
	vp2+=newVp2;
  } 
  // Uncomment in order to try earlier programs
  //  Bottom Left
  //SetVP(0.0, 0.0, 0.5, 0.5);
  //drawCube();
  //  Bottom Right
 // SetVP(0.5, 0.0, 1.0, 0.5);
  //drawCube();
  //  Top Left
  //SetVP(0.0, 0.5, 0.5, 1.0);
  //drawCube();
  //  Top Right
  //SetVP(0.5, 0.5, 1.0, 1.0);
  //drawCube();

  glFlush(); 
}

void init() 
{
	struct VertexData {
		vec4 color;
		vec4 position;
	};
	
  	VertexData vertices[NUMVERTICES] = {
		// color, position
		// Two reptitions of the tile were needed to fill the window
		// TESSELLATION TILE 1:
		//Quad 1, Triangle 1: light blue
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(-1.0, 0.0, 0.0, 1.0)},	// A - 
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(-1.0, 0.67, 0.0, 1.0)},  	// B - 
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(-0.5, 1.0, 0.0, 1.0)},	// C - 
		//Quad 1, Triangle 2: light blue
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(-0.5, 1.0, 0.0, 1.0)},	// C - 
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(-0.5, 0.33, 0.0, 1.0)},	// D - 
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(-1.0, 0.0, 0.0, 1.0)},	// A - 
		//Quad 2, Triangle 1: ocean blue
		{vec4(0.0, 0.4, 0.8, 1.0),   vec4(0.0, 0.0, 0.0, 1.0)},		// F - 
		{vec4(0.0, 0.4, 0.8, 1.0),   vec4(0.0, 0.67, 0.0, 1.0)},  	// E - 
		{vec4(0.0, 0.4, 0.8, 1.0),   vec4(-0.5, 1.0, 0.0, 1.0)},  	// C -
		//Quad 2, Triangle 2: ocean blue
		{vec4(0.0, 0.4, 0.8, 1.0),   vec4(-0.5, 1.0, 0.0, 1.0)},  	// C - 
		{vec4(0.0, 0.4, 0.8, 1.0),   vec4(-0.5, 0.33, 0.0, 1.0)},	// D - 
		{vec4(0.0, 0.4, 0.8, 1.0),   vec4(0.0, 0.0, 0.0, 1.0)},		// F - 
		//Quad 3, Triangle 1: ocean blue
		{vec4(0.0, 0.4, 0.8, 1.0),   vec4(-1.0, 0.0, 0.0, 1.0)},	// A - 
		{vec4(0.0, 0.4, 0.8, 1.0),   vec4(-1.0, -0.67, 0.0, 1.0)},	// H - 
		{vec4(0.0, 0.4, 0.8, 1.0),   vec4(-0.5, -1.0, 0.0, 1.0)},	// I - 
		//Quad 3, Triangle 2: ocean blue
		{vec4(0.0, 0.4, 0.8, 1.0),   vec4(-0.5, -1.0, 0.0, 1.0)},	// I - 
		{vec4(0.0, 0.4, 0.8, 1.0),   vec4(-0.5, -0.33, 0.0, 1.0)},	// G - 
		{vec4(0.0, 0.4, 0.8, 1.0),   vec4(-1.0, 0.0, 0.0, 1.0)},	// A -
		//Quad 4, Triangle 1: light blue
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(-0.5, -1.0, 0.0, 1.0)},	// I - 
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(0.0, -0.67, 0.0, 1.0)},	// J - 
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(0.0, 0.0, 0.0, 1.0)},		// F - 
		//Quad 4: Triangle 2: light
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(-0.5, -1.0, 0.0, 1.0)},	// I - 
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(-0.5, -0.33, 0.0, 1.0)},	// G - 
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(0.0, 0.0, 0.0, 1.0)},		// F - 
		 
		// TESSELLATION TILE 2:
		//Quad 1, Triangle 1: light blue
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(0.0, 0.0, 0.0, 1.0)},		// A - 
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(0.0, 0.67, 0.0, 1.0)},  	// B - 
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(0.5, 1.0, 0.0, 1.0)},		// C
		//Quad 1, Triangle 2: light blue
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(0.5, 1.0, 0.0, 1.0)},		// C -
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(0.5, 0.33, 0.0, 1.0)},	// D - 
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(0.0, 0.0, 0.0, 1.0)},		// A - 
		//Quad 2, Triangle 2: ocean blue 
		{vec4(0.0, 0.4, 0.8,1.0),   vec4(1.0, 0.0, 0.0, 1.0)},		// F -
		{vec4(0.0, 0.4, 0.8,1.0),   vec4(1.0, 0.67, 0.0, 1.0)},  	// E -  
		{vec4(0.0, 0.4, 0.8,1.0),   vec4(0.5, 1.0, 0.0, 1.0)},  	// C - 
		//Quad 2, Triangle 2: ocean blue
		{vec4(0.0, 0.4, 0.8,1.0),   vec4(0.5, 1.0, 0.0, 1.0)},  	// C - 
		{vec4(0.0, 0.4, 0.8,1.0),   vec4(0.5, 0.33, 0.0, 1.0)},		// D - 
		{vec4(0.0, 0.4, 0.8,1.0),   vec4(1.0, 0.0, 0.0, 1.0)},		// F -
		//Quad 3, Triangle 1: ocean blue
		{vec4(0.0, 0.4, 0.8, 1.0),   vec4(0.0, 0.0, 0.0, 1.0)},		// A - 
		{vec4(0.0, 0.4, 0.8, 1.0),   vec4(0.0, -0.67, 0.0, 1.0)},	// H - 
		{vec4(0.0, 0.4, 0.8, 1.0),   vec4(0.5, -1.0, 0.0, 1.0)},	// I -
		//Quad 3, Triangle 2: ocean blue
		{vec4(0.0, 0.4, 0.8, 1.0),   vec4(0.5, -1.0, 0.0, 1.0)},	// I -
		{vec4(0.0, 0.4, 0.8, 1.0),   vec4(0.5, -0.33, 0.0, 1.0)},	// G - 
		{vec4(0.0, 0.4, 0.8, 1.0),   vec4(0.0, 0.0, 0.0, 1.0)},		// A - 
		//Quad 4, Triangle 1: light blue	
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(0.5, -1.0, 0.0, 1.0)},	// I -
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(1.0, -0.67, 0.0, 1.0)},	// J -
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(1.0, 0.0, 0.0, 1.0)},		// F -
		//Quad 4: Triangle 2: light blue
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(0.5, -1.0, 0.0, 1.0)},	// I -
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(0.5, -0.33, 0.0, 1.0)},	// G -
		{vec4(0.4, 0.7, 1.0, 1.0),   vec4(1.0, 0.0, 0.0, 1.0)},		// F -
	};
	 

  // Specify the vertices for a triangle, along with a color for each:

  // Create a vertex array object
  GLuint vao[1];
  #ifdef __APPLE__       // For use with OS X
    glGenVertexArraysAPPLE(1, vao );
    glBindVertexArrayAPPLE(vao[0] );
  #else		       // Other (Linux)
    glGenVertexArrays(1, vao );
    glBindVertexArray(vao[0] );       
  #endif
  
  // Create and initialize a buffer object
  GLuint buffer;
  glGenBuffers( 1, &buffer );
  glBindBuffer( GL_ARRAY_BUFFER, buffer );
  glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
  GLuint program = InitShader( "vshader_tile.glsl", "fshader_tile.glsl" );
  glUseProgram( program );
  
  // Initialize the vertex color attribute
  glPointSize(3.0);
  GLuint color_location = glGetAttribLocation( program, "vColor" );
  glEnableVertexAttribArray(color_location);
  glVertexAttribPointer(color_location, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), BUFFER_OFFSET(0) );

  // Initialize the vertex position attribute
  GLuint position_location = glGetAttribLocation( program, "vPosition");
  glEnableVertexAttribArray(position_location);
  glVertexAttribPointer(position_location, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), BUFFER_OFFSET(sizeof(vertices[0].color)));
  
  glEnableVertexAttribArray(vColor);
  glEnableVertexAttribArray(vPosition);
  
  /* set clear color to white-blue to fit color scheme */
  glClearColor (0.8, 0.9, 1.0, 1.0);

  //std::cout<<glGetString(GL_SHADING_LANGUAGE_VERSION) ;

}

//// drawCube()
// Precondition: All coordinates of type vec4 have been entered correctly so that color and vertex attributes will appear as intended
// Postcondition: By default, the design from the vertices array will be drawn from index 0, to the last index of the array
// Wireframe can then be toggled on and off, though it is not necessary to the program

void drawCube()
{
	if (wireframe)
	  {
			glLineWidth(5.0);
		  	glDrawArrays(GL_LINE_LOOP, 0, NUMVERTICES);
	  };
	  if (filled)
	  {	
			glDrawArrays(GL_TRIANGLES, 0, NUMVERTICES);
	  };
}


void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:     //ESC
         exit(0);
         break;
  	  case 'w':   //wireframe
		wireframe = true;
		filled = false;
		glutPostRedisplay();
		break;
	  case 'f':   //filled
		wireframe = false;
		filled = true;
		glutPostRedisplay();
		break;
   }
}

//// SetVP() 
/*Preconditon: leftx, lefty are the x,y coordinates of the lower left corner of the viewport rectangle to be set; rightx and righty are the x,y coordinates of the upper right corner of the rectangle.  Both sets of coordinates are given in percentages of the screen window.  For example, if leftx=0.25 and lefty=0.5, the lower left corner of the viewport has been set to a pixel that is 25% from the left side of the window and 50% from the bottom.
 *Postcondition:  the appropriate viewport has been set.
*/
void SetVP(double leftx,double lefty,double rightx, double righty)
{
	// in form (left, bottom, right, top) : 
	glViewport(leftx * (window_width), lefty * (window_height), (rightx - leftx) * (window_width), (righty - lefty) * (window_height));
	
	// in form (left, right, bottom, top) : 
	//glViewport(leftx * (window_width/2.0), rightx * (window_width/2.0), rightx * (window_height/2.0), righty * (window_height / 2.0));
}




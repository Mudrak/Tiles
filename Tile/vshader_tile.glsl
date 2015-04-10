attribute vec4 vColor, vPosition;
varying vec4 color;

void main()
{
	color = vColor;
	gl_Position = vPosition;
}

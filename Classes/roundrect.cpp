#include "cocos2d.h"

USING_NS_CC;


/* ========================================================================================
=  Add these methods to a file that gets included in your .pch or add these directly to  =
=  CCDrawingPrimitives.h and .m                                                          =
==========================================================================================*/
/**
*  Draws the given vertices and fills in the inside.
*
*  @param vertices Array of ccVertex2F to draw.
*  @param numberOfPoints Number of vertices in the array.
*/
void ccDrawVerticiesFilled(const ccVertex2F *vertices, int numberOfPoints)
{

	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);

	glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei)numberOfPoints);
}



/**
*  Adds vertices for a bezier curve with the given parameters to an array of vertices. It uses the same
*  implementation as ccDrawCubicBezier in CCDrawingPrimitives for vertex creation.
*
*  @param origin Starting point for our curve.
*  @param control1 Control point for bending the curve before the halfway point.
*  @param control2 Control point for bending the curve after the halfwar point.
*  @param destination Ending point for our curve.
*  @param segments Number of segments we want in the curve.
*  @param vertices Pointer to an array of vertices that we'll be adding the curve vertices to.
*/
void addCubicBezierVertices(CCPoint origin, CCPoint control1, CCPoint control2, CCPoint destination, int segments, ccVertex2F *vertices)
{
	int totalSegments = segments - 1;
	float t = 0;
	for (int i = 0; i < totalSegments; i++)
	{
		ccVertex2F vertex;
		vertex.x = powf(1 - t, 3) * origin.x + 3.0f * powf(1 - t, 2) * t * control1.x + 3.0f * (1 - t) * t * t * control2.x + t * t * t * destination.x;
		vertex.y = powf(1 - t, 3) * origin.y + 3.0f * powf(1 - t, 2) * t * control1.y + 3.0f * (1 - t) * t * t * control2.y + t * t * t * destination.y;
		vertices[i] = vertex;
		t += 1.0f / totalSegments;
	}

	ccVertex2F finalVertex = vertex2(destination.x, destination.y);
	vertices[totalSegments] = finalVertex;
}

/**
*  Draws a rounded rectangle.
*
*  @param rect The rectangle to draw.
*  @param cornerRadius The radius of the corners.
*  @param smoothness A multiplier for the number of segments drawn for each corner. 2 or 3 is recommended.
*  @param cornersToRound An array of BOOL values that signifies which corners we should round. The indices
*          represent each corner as follows: 0 -> bottomLeft, 1 -> topLeft, 2 -> topRight, 3 -> bottomRight.
*/
void ccDrawSolidRoundedRect(CCRect rect, int cornerRadius, int smoothness, bool *cornersToRound) {
	CCPoint origin = rect.origin;
	CCSize size = rect.size;

	// number of segments for each rounded corner, +1 for end point of the curve  
	int roundedCornerSegments = cornerRadius * smoothness + 1;

	// get the total vertices we'll need to draw  
	int totalVertices = 0;
	for (int i = 0; i < 4; i++) {
		// add number of vertices needed for a rounded corner if we're rounding it,  
		// else just add 1 vertex for the corner  
		if (cornersToRound[i]) {
			totalVertices += roundedCornerSegments;
		}
		else {
			totalVertices += 1;
		}
	}

	ccVertex2F *vertices = new ccVertex2F[totalVertices];

	// create the vertices we're going to draw in clockwise fashion starting from bottom left corner  
	int currentVertexIndex = 0;
	for (int i = 0; i < 4; i++) {
		// if we don't want to draw the rounded corner just add a vertex at the corner point  
		if (!cornersToRound[i]) {
			switch (i) {
			case 0: vertices[currentVertexIndex] = vertex2(origin.x, origin.y); break;
			case 1: vertices[currentVertexIndex] = vertex2( origin.x, origin.y + size.height ); break;
			case 2: vertices[currentVertexIndex] = vertex2( origin.x + size.width, origin.y + size.height ); break;
			case 3: vertices[currentVertexIndex] = vertex2( origin.x + size.width, origin.y ); break;
			default: break;
			}
			currentVertexIndex++;
		}
		else {
			// we want the corner rounded so add vertices for that rounded corner  
			switch (i) {
			case 0: addCubicBezierVertices(ccp(origin.x + cornerRadius, origin.y),
				ccp(origin.x + cornerRadius / 2, origin.y),
				ccp(origin.x, origin.y + cornerRadius / 2),
				ccp(origin.x, origin.y + cornerRadius),
				roundedCornerSegments, &vertices[currentVertexIndex]); break;
			case 1: addCubicBezierVertices(ccp(origin.x, origin.y + size.height - cornerRadius),
				ccp(origin.x, origin.y + size.height - cornerRadius / 2),
				ccp(origin.x + cornerRadius / 2, origin.y + size.height),
				ccp(origin.x + cornerRadius, origin.y + size.height),
				roundedCornerSegments, &vertices[currentVertexIndex]); break;
			case 2: addCubicBezierVertices(ccp(origin.x + size.width - cornerRadius, origin.y + size.height),
				ccp(origin.x + size.width - cornerRadius / 2, origin.y + size.height),
				ccp(origin.x + size.width, origin.y + size.height - cornerRadius / 2),
				ccp(origin.x + size.width, origin.y + size.height - cornerRadius),
				roundedCornerSegments, &vertices[currentVertexIndex]); break;
			case 3: addCubicBezierVertices(ccp(origin.x + size.width, origin.y + cornerRadius),
				ccp(origin.x + size.width, origin.y + cornerRadius / 2),
				ccp(origin.x + size.width - cornerRadius / 2, origin.y),
				ccp(origin.x + size.width - cornerRadius, origin.y),
				roundedCornerSegments, &vertices[currentVertexIndex]); break;
			default: break;
			}
			currentVertexIndex += roundedCornerSegments;
		}
	}

	// we now have all the vertices we need so draw them  
	ccDrawVerticiesFilled(vertices, totalVertices);

	delete[]vertices;
}




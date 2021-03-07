//defines a Context for storing Opengl state

#ifndef Context_h
#define Context_h

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

	//create info for the context
	typedef struct
	{
		bool GLFWIsInit; //tells it to init GLFW or not
		bool enableCulling, enableBlending, enableDepthBuffer; //render settings

	} Glfix_Context_CreateInfo;

	//inits a default Create Info
	void Glfix_Context_InitCreateInfo(Glfix_Context_CreateInfo* info);

	//defines the context
	typedef struct
	{
		//render states
		bool depthBufferIsEnabled;

		//stores a window in case Glfix has to init GLFW
		void* window;

	} Glfix_Context_Context;

	//creates the Context
	Glfix_Context_Context* Glfix_Context_Create(Glfix_Context_CreateInfo* info);
	//destroys the Context
	void Glfix_Context_Destroy(Glfix_Context_Context* context);

	//clears the screen
	void Glfix_Context_Clear(Glfix_Context_Context* context);
	//sets the clear color
	void Glfix_Context_SetClearColor(float r, float g, float b, float a);
	//sets the clear color || expects a 4 element array
	void Glfix_Context_SetClearColorVec4(float* color);

	//resizes the view port
	void Glfix_Context_SetViewPort(int32_t xPos, int32_t yPos, int32_t width, int32_t height);

	//enables or disables face culling
	void Glfix_Context_EnableFaceCulling(bool state);
	//enables or disables blending
	void Glfix_Context_EnableBlending(bool state);
	//enables or disables Z buffer
	void Glfix_Context_EnableDepthBuffer(Glfix_Context_Context* context, bool state);

#ifdef __cplusplus
}
#endif

#endif
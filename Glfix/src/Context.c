#include <gpch.h>
#include <Glfix\Context.h>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

//stores the state
static bool GLFIX_HAS_INITED_GLFW = false;

//inits a default Create Info
void Glfix_Context_InitCreateInfo(Glfix_Context_CreateInfo* info)
{
	if (!info)
	{
		LogError("NULL Create Info", "A valid pointer must be give to \"Context: Init Create Info\" so it can write data!");
		return;
	}

	info->enableBlending = false;
	info->enableCulling = false;
	info->enableDepthBuffer = false;
	info->GLFWIsInit = false;
}

//creates the Context
Glfix_Context_Context* Glfix_Context_Create(Glfix_Context_CreateInfo* info)
{
	if (!info)
	{
		LogError("NULL Create Info", "A valid pointer must be give to \"Context: Create\" so it can use the data!");
		return NULL;
	}

	//allocate context
	Glfix_Context_Context* context = malloc(sizeof(Glfix_Context_Context));
	context->window = NULL;

	//if GLFW is not inited by the app, Glfix will do it
	if (!info->GLFWIsInit)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_VISIBLE, false);
		context->window = glfwCreateWindow(1, 1, "", NULL, NULL);

		//if failed to make window
		if (!context->window)
		{
			LogError("GLFW NULL Context", "Since GLFW was not used in the app, Glfix tried to make it's own and failed!");
			Glfix_Context_Destroy(context);
			return NULL;
		}
		glfwMakeContextCurrent(context->window);
	}

	//init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LogError("GLAD NULL Context", "Failed to initialize GLAD");
		Glfix_Context_Destroy(context);
		return NULL;
	}

	Glfix_Context_EnableBlending(info->enableBlending);
	Glfix_Context_EnableFaceCulling(info->enableCulling);
	Glfix_Context_EnableDepthBuffer(context, info->enableDepthBuffer);

	return context;
}

//destroys the Context
void Glfix_Context_Destroy(Glfix_Context_Context* context)
{
	if (!context)
	{
		LogWarning("NULL Context", "Context is NULL can not destroy!");
		return;
	}

	//clean up window
	if (context->window)
	{
		glfwDestroyWindow(context->window);
		if (context->window)
		{
			free(context->window);
			context->window = NULL;
		}
	}

	//if GLFW is not destroyed by the app, Glfix will do it
	if (GLFIX_HAS_INITED_GLFW)
	{
		glfwTerminate();
		GLFIX_HAS_INITED_GLFW = false;
	}

	free(context);
	context = NULL;
}

//clears the screen
void Glfix_Context_Clear(Glfix_Context_Context* context)
{
	if (!context)
	{
		LogWarning("NULL Context", "Context must be passed to \"Context: Clear\" in order for depth buffer checking.");
		glClear(GL_COLOR_BUFFER_BIT);
	}

	(context->depthBufferIsEnabled == true ? glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) :
		glClear(GL_COLOR_BUFFER_BIT));
}

//sets the clear color
void Glfix_Context_SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

//sets the clear color || expects a 4 element array
void Glfix_Context_SetClearColorVec4(float* color)
{
	glClearColor(color[0], color[1], color[2], color[3]);
}

//resizes the view port
void Glfix_Context_SetViewPort(int32_t xPos, int32_t yPos, int32_t width, int32_t height)
{
	glViewport(xPos, yPos, width, height);
}

//enables or disables face culling
void Glfix_Context_EnableFaceCulling(bool state)
{
	(state == true ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE));
}

//enables or disables blending
void Glfix_Context_EnableBlending(bool state)
{
	if (state)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
		glDisable(GL_BLEND);
}

//enables or disables Z buffer
void Glfix_Context_EnableDepthBuffer(Glfix_Context_Context* context, bool state)
{
	if (!context)
	{
		LogWarning("NULL Context", "Context is NULL can not update Z buffer state!");
		return;
	}

	(state == true ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST));
	context->depthBufferIsEnabled = state;
}
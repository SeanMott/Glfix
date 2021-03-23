#include <gpch.hpp>
#include <Glfix\Context.hpp>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

//stores the state
static bool GLFIX_HAS_INITED_GLFW = false;

Glfix::Context* Glfix::Context::Create(ContextCreateInfo& info)
{
	//allocate context
	Context* context = new Context();

	//if GLFW is not inited by the app, Glfix will do it
	if (!info.GLFWIsInit && !GLFIX_HAS_INITED_GLFW)
	{
		if (!glfwInit())
		{
			LogError("Failed GLFW", "Failed to init GLFW!");
			delete context;
			context = nullptr;
			return nullptr;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, info.openglMajorVer);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, info.openglMinorVer);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_VISIBLE, false);
		context->window = glfwCreateWindow(1, 1, "", NULL, NULL);

		//if failed to make window
		if (!context->window)
		{
			LogError("GLFW NULL Context", "Since GLFW was not used in the app, Glfix tried to make it's own and failed!");
			delete context;
			context = nullptr;
			return nullptr;
		}
		glfwMakeContextCurrent(((GLFWwindow*)context->window));

		info.viewPortWidth = 1; info.viewPortHeight = 1;
		GLFIX_HAS_INITED_GLFW = true;
	}

	//init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LogError("GLAD NULL Context", "Failed to initialize GLAD");
		delete context;
		context = nullptr;
		return nullptr;
	}

	context->EnableBlending(info.enableBlending);
	context->EnableFaceCulling(info.enableFaceCulling);
	context->EnableDepthBuffer(info.enableDepthBuffer);
	context->SetViewPort(0, 0, info.viewPortWidth, info.viewPortHeight);

	return context;
}

std::unique_ptr<Glfix::Context> Glfix::Context::SCreate(ContextCreateInfo& info)
{
	//allocate context
	std::unique_ptr<Context> context = std::make_unique< Context>();

	//if GLFW is not inited by the app, Glfix will do it
	if (!info.GLFWIsInit && !GLFIX_HAS_INITED_GLFW)
	{
		if (!glfwInit())
		{
			LogError("Failed GLFW", "Failed to init GLFW!");
			context.reset();
			context = nullptr;
			return nullptr;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, info.openglMajorVer);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, info.openglMinorVer);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_VISIBLE, false);
		context->window = glfwCreateWindow(1, 1, "", NULL, NULL);

		//if failed to make window
		if (!context->window)
		{
			LogError("GLFW NULL Context", "Since GLFW was not used in the app, Glfix tried to make it's own and failed!");
			context.reset();
			context = nullptr;
			return nullptr;
		}
		glfwMakeContextCurrent(((GLFWwindow*)context->window));

		info.viewPortWidth = 1; info.viewPortHeight = 1;
		GLFIX_HAS_INITED_GLFW = true;
	}

	//init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LogError("GLAD NULL Context", "Failed to initialize GLAD");
		context.reset();
		context = nullptr;
		return nullptr;
	}

	context->EnableBlending(info.enableBlending);
	context->EnableFaceCulling(info.enableFaceCulling);
	context->EnableDepthBuffer(info.enableDepthBuffer);
	context->SetViewPort(0, 0, info.viewPortWidth, info.viewPortHeight);

	return context;
}

void Glfix::Context::Destroy()
{
	//clean up window
	if (window)
	{
		glfwDestroyWindow(((GLFWwindow*)window));
		if (window)
		{
			free(window);
			window = nullptr;
		}
	}

	//if GLFW is not destroyed by the app, Glfix will do it
	if (GLFIX_HAS_INITED_GLFW)
	{
		glfwTerminate();
		GLFIX_HAS_INITED_GLFW = false;
	}
}

void Glfix::Context::SetClearColor(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
}

void Glfix::Context::SetClearColor(float* color) const
{
	if (!color)
	{
		LogError("NULL Color", "A 4 element float array must be give to \"Glfix::Context::SetClearColor\" yours was a nullptr!");
		return;
	}

	glClearColor(color[0], color[1], color[2], color[3]);
}

void Glfix::Context::Clear() const
{
	(depthBufferIsEnabled == true ? glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) :
		glClear(GL_COLOR_BUFFER_BIT));
}

void Glfix::Context::EnableFaceCulling(bool state) const
{
	(state == true ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE));
}

void Glfix::Context::EnableBlending(bool state) const
{
	if (state)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
		glDisable(GL_BLEND);
}

void Glfix::Context::EnableDepthBuffer(bool state)
{
	(state == true ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST));
	depthBufferIsEnabled = state;
}

void Glfix::Context::SetViewPort(int32_t xPos, int32_t yPos, int32_t width, int32_t height) const
{
	glViewport(xPos, yPos, width, height);
}

//defines the C++ Context

#ifndef Context_h
#define Context_h

#include <cstdint>
#include <memory>

namespace Glfix
{
	//the create info
	struct ContextCreateInfo
	{
		//the settings
		bool enableBlending = false, enableFaceCulling = false, enableDepthBuffer = false;

		//the viewport size
		uint32_t viewPortWidth = 800, viewPortHeight = 600;

		//if GLFW needs to be inited by the Context
		bool GLFWIsInit = true;
		uint32_t openglMinorVer = 3, openglMajorVer = 3;

	};

	//the Context
	class Context
	{
		//vars
	private:

		bool depthBufferIsEnabled = false; //is needed when clearing the screen
		void* window = nullptr; //stored only if it has to init GLFW

		//methods
	public:

		//Deconstructor
		~Context() { Destroy(); }

		//creates a Context
		static Context* Create(ContextCreateInfo& info);
		//creates a Unique Pointer Context
		static std::unique_ptr<Context> SCreate(ContextCreateInfo& info);
		//destroys the Context
		void Destroy();

		//sets the clear color
		void SetClearColor(float r, float g, float b, float a) const;
		//sets the clear color || expects a 4 element array
		void SetClearColor(float* color) const;

		//clears the screen
		void Clear() const;

		//sets if face culling should be used
		void EnableFaceCulling(bool state) const;
		//sets if blending should be used
		void EnableBlending(bool state) const;
		//sets if the depth buffer should be used
		void EnableDepthBuffer(bool state);
		//sets the view port
		void SetViewPort(int32_t xPos, int32_t yPos, int32_t width, int32_t height) const;
	};
}

#endif
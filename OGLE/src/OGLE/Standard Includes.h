#pragma once

//Main.cpp
	#include "oglepch.h"
	// EntryPoint
		// Base
			// Platform Detection
			// Assert
				// Log
					//Base // LOOP

		// Application
			//Base.h

			// Window
				//Base.h
				//Event.h
				// OpenGLContext
					//OpenGL 
						#include <GLFW/glfw3.h>
						#include <glad/glad.h>
				#include <sstream>
			// LayerStack
				//Base
				// Layer
					//Base
					// Timestep
						//NONE
					//Event
				#include <vector>

			// Event
				// Instrumentor
					//Log.h
					#include <algorithm>
					#include <chrono>
					#include <fstream>
					#include <iomanip>
					#include <string>
					#include <thread>
					#include <mutex>
					#include <sstream>
				//Base.h

				#include <functional>
			// ApplicationEvent
				//Event

			//Timestep.h

			// ImGuiLayer
				//Layer

				//ApplicationEvent
				// KeyEvent
					//Event

					// KeyCodes
						// Control
							//NONE

				// MouseEvent
					//Event
					// MouseCodes
						//glm
						//Control	


			// Renderer
				// Shader
					// VertexArray
						// Buffer
							// Vertex
								// VertexAttributeArray
									// VertexAttribute
										//OpenGLContext
				// Camera
					// Input
						//KeyCodes
						//MouseCodes

		// HelloLayer
			//Layer
			//Renderer



















#include "CameraController.h"

CameraController::CameraController()
{
	m_CameraRotation = vec3(0.0f, radians(270.0f), 0.0f);
	m_CameraPosition = vec3(0.0f, 25.0f, 90.0f);

	m_CameraLookAtPosition = vec3(cos(m_CameraRotation.y), 0, sin(m_CameraRotation.y));
}

CameraController::~CameraController()
{
}

//takes a string of a direction and returns a vector in that direction.
//the returned vector uses trigonometry to return the components needed 
//to move one unit forwards whilst still moving at an angle

vec3 CameraController::collisionCheck(string direction)
{
	if (direction == "Forward")
	{
		return m_CameraPosition + vec3(-sin(m_CameraRotation.y - radians(90.0f)), 0.0f, cos(m_CameraRotation.y - radians(90.0f)));
	}
	else if (direction == "Backward")
	{
		return m_CameraPosition - vec3(-sin(m_CameraRotation.y - radians(90.0f)), 0.0f, cos(m_CameraRotation.y - radians(90.0f)));
	}
	else if (direction == "Right")
	{
		return m_CameraPosition + vec3(-sin(m_CameraRotation.y), 0.0f, cos(m_CameraRotation.y));
	}
	else
	{
		return m_CameraPosition - vec3(-sin(m_CameraRotation.y), 0.0f, cos(m_CameraRotation.y));
	}
}

//Takes a string for a direction then moves one unit in that direction
//The formula for working out the movement is the same as used previously
void CameraController::move(string direction)
{
	if (direction == "Forward")
	{
		m_CameraPosition += vec3(-sin(m_CameraRotation.y - radians(90.0f)), 0.0f, cos(m_CameraRotation.y - radians(90.0f)));
	}
	else if (direction == "Backward")
	{
		m_CameraPosition -= vec3(-sin(m_CameraRotation.y - radians(90.0f)), 0.0f, cos(m_CameraRotation.y - radians(90.0f)));
	}
	else if (direction == "Right")
	{
		m_CameraPosition += vec3(-sin(m_CameraRotation.y), 0.0f, cos(m_CameraRotation.y));
	}
	else
	{
		m_CameraPosition -= vec3(-sin(m_CameraRotation.y), 0.0f, cos(m_CameraRotation.y));
	}

//The camera look at position is a vector that is added on to current position of the camera.
//This is used when determining what the camera should be looking at.
	m_CameraLookAtPosition = vec3(cos(m_CameraRotation.y), -tan(m_CameraRotation.x), sin(m_CameraRotation.y));
}

	//This function takes the change in of mouse position in the x and y
void CameraController::mouseRotation(float x, float y)
{
//it changes the rotation of the camera using the change in the x and y
	m_CameraRotation += vec3(radians(y/2), radians(x/2), 0.0f);

//if limits how far up and down the player can look.	
	if (m_CameraRotation.x < radians(-80.0f))
		m_CameraRotation += vec3(radians(-y/2), 0.0f, 0.0f);

	if (m_CameraRotation.x > radians(80.0f))
		m_CameraRotation += vec3(radians(-y/2), 0.0f, 0.0f);

	m_CameraLookAtPosition = vec3(cos(m_CameraRotation.y), -tan(m_CameraRotation.x), sin(m_CameraRotation.y));
}

void CameraController::onUpdate()
{
//controls the physics of the camera
//If the player is jumping they move up
//once they reach the peak of their jump they are  no longer jumping
//And the player moves downwards at an increasing speed.

	if (m_Force <= 0.1 && m_Jumping)
	{
		m_Jumping = false;
	}

	if (!m_Jumping && !m_Grounded)
	{
		m_CameraPosition -= vec3(0.0f, m_Force, 0.0f);
		m_Force += 0.1;
		if (m_Force < -24)
		{
			m_Force -= 0.1;
		}
	}

	if (m_Force > 0.1 && m_Jumping)
	{
		m_CameraPosition += vec3(0.0f, m_Force, 0.0f);
		m_Force -= 0.1;
	}

//If there is a game object below the camera it does not move up or down
	if (m_Grounded && !m_Jumping)
	{
		m_Force = 0.0f;
	}

	//cout << m_Force << " " << m_Grounded << "\n";
}

//If debug mode is on the camera moves up
//if it is not it sets the boolean jumping to true and sets a force
void CameraController::jump(bool debug)
{
	if (!debug)
	{
		if (m_Grounded)
		{
			m_Force = 4.0f;
			m_Jumping = true;
		}
	}
	else
	{
		m_CameraPosition += vec3(0.0f, 3.0f, 0.0f);
	}

}

//moves the camera down
void CameraController::down()
{
	m_CameraPosition -= vec3(0.0f, 1.0f, 0.0f);
}


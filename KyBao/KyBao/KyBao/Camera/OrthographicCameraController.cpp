#include "kbpch.h"
#include "KyBao/Camera/OrthographicCameraController.h"
#include "KyBao/Core/Input.h"
#include "KyBao/Core/KeyCodes.h"
#include <KyBao/Core/Application.h>
namespace KyBao {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{

	}
	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(Key::Left))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(Key::Right))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		if (Input::IsKeyPressed(Key::Down))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(Key::Up))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(Key::Q))
				m_Rotation -= m_CameraRotationSpeed;
			else if (Input::IsKeyPressed(Key::R))
				m_Rotation += m_CameraRotationSpeed;
			m_Camera.SetRotation(m_Rotation);
		}
		m_Camera.SetPosition(m_CameraPosition);
	}
	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}
	void OrthographicCameraController::OnResize(float width, float height)
	{

		m_AspectRatio = width / height;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = (((m_ZoomLevel) > (0.25f)) ? (m_ZoomLevel) : (0.25f));
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}
}
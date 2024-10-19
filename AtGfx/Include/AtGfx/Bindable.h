#pragma once

namespace AtGfx::Internal
{

	class Bindable
	{
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};

}

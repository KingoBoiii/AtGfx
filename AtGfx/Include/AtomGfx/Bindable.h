#pragma once

namespace AtomGfx::Internal
{

	class Bindable
	{
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};

}


#pragma once


namespace framework
{

	class cGameMain
	{
	public:
		cGameMain();
		virtual ~cGameMain();

		virtual void Run();
		virtual void Update();
		virtual void Render();

	};
}

#include "gmpch.h"
#include "Layer.h"

namespace EopGuiMaker {

	Layer::Layer(std::string debug_name)
		: m_DebugName(std::move(debug_name))
	{
	}

	Layer::~Layer()
	= default;
}

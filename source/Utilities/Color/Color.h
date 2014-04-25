#ifndef UTILITIES_COLOR_H
#define UTILITIES_COLOR_H

#include "GLM/include/glm/glm.hpp"
#include "GLM/include/glm/core/_detail.hpp"

namespace Atum
{
namespace Utilities
{

	template <typename type>
	class Color
	{
	public:
		Color();
		Color(glm::detail::tvec4<type> color);
		Color(type r, type g, type b, type a);
		~Color();

		// Getter
		glm::detail::tvec4<type> GetColor() const;
		type R() const;
		type G() const;
		type B() const;
		type A() const;

		// Setter
		void SetColor(glm::detail::tvec4<type> color);
		void SetR(type r);
		void SetG(type g);
		void SetB(type b);
		void SetA(type a);

	private:
		glm::detail::tvec4<type> m_color;

	};

	template <typename type>
	Color<type>::Color()
	{}


	template <typename type>
	Color<type>::Color( glm::detail::tvec4<type> color )
	{
		SetColor(color);
	}

	template <typename type>
	Color<type>::Color( type r, type g, type b, type a )
	{
		SetR(r);
		SetB(b);
		SetG(g);
		SetA(a);
	}

	template <typename type>
	Color<type>::~Color()
	{}

	template <typename type>
	inline glm::detail::tvec4<type> Color<type>::GetColor() const { return m_color; }

	template <typename type>
	inline type Color<type>::R() const { return m_color.r; }
	template <typename type>
	inline type Color<type>::G() const { return m_color.g; }
	template <typename type>
	inline type Color<type>::B() const { return m_color.b; }
	template <typename type>
	inline type Color<type>::A() const { return m_color.a; }
	template <typename type>
	inline void Color<type>::SetColor(glm::detail::tvec4<type> color){ m_color = color; }
	template <typename type>
	inline void Color<type>::SetR(type r) { m_color.r = r; }
	template <typename type>
	inline void Color<type>::SetG(type g) { m_color.g = g; }
	template <typename type>
	inline void Color<type>::SetB(type b) { m_color.b = b; }
	template <typename type>
	inline void Color<type>::SetA(type a) { m_color.a = a; }

} // namespace Utilities
} // namespace Atum



#endif

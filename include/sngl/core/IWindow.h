#ifndef _SNGL_CORE_IWINDOW_H_INCLUDED_
#define _SNGL_CORE_IWINDOW_H_INCLUDED_

#include <string>

namespace sngl::core
{
   class IWindow
   {
   public:
      virtual ~IWindow() = default;

      virtual void setTitle(const std::string_view title) = 0;
      virtual const std::string_view getTitle() const = 0;
   };
}

#endif
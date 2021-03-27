#include "Canvas.hpp"
#include "CanvasImplementation.hpp"

Canvas& Canvas::operator=(Canvas&& move_form) noexcept{

    if (&move_form == this) return *this;

    std::swap(impl_, move_form.impl_);

    return *this;

}

Canvas::Canvas() : impl_{ } {

    try {

        impl_ = new CanvasImplementation{};

    }
    catch (const std::bad_alloc&) {

        throw ComponentException{ u8"Canvas allocation memory error." };

    }

}

Canvas::Canvas(Canvas&& move_form) noexcept :
    impl_{ } {

    std::swap(impl_, move_form.impl_);

}

Canvas::~Canvas() noexcept{

    if (impl_.has_value())
        delete std::any_cast<CanvasImplementation*>(impl_);

}

const uint64_t Canvas::GetWidth() const noexcept{

    return std::any_cast<CanvasImplementation*>(impl_)->GetWidth();
}

const uint64_t Canvas::GetHeight() const noexcept{

    return std::any_cast<CanvasImplementation*>(impl_)->GetHeight();

}

const uint64_t Canvas::GetX() const noexcept
{
    return std::any_cast<CanvasImplementation*>(impl_)->GetX();
}

const uint64_t Canvas::GetY() const noexcept
{
    return std::any_cast<CanvasImplementation*>(impl_)->GetY();
}

Color Canvas::GetDefaultBackgroundColor() const noexcept{

    return Color{ CanvasImplementation::kDefaultBackgroundColor };
    
}

void Canvas::Line(uint64_t x, uint64_t y, uint64_t _x, uint64_t _y, const Color& color) noexcept{

    std::any_cast<CanvasImplementation*>(impl_)->Line(x, y, _x, _y, color);

}

void Canvas::Line(uint64_t x, uint64_t y, uint64_t _x, uint64_t _y, uint64_t line_thickness, const Color& color) noexcept{

    std::any_cast<CanvasImplementation*>(impl_)->Line(x, y, _x, _y, line_thickness, color);

}

void Canvas::Create(const HWND parent_hWnd) {

    std::any_cast<CanvasImplementation*>(impl_)->Create(parent_hWnd);

}

void Canvas::SetCanvasProc(ProcessMessage process_canvas) noexcept{

    std::any_cast<CanvasImplementation*>(impl_)->SetCanvasProc(process_canvas);

}

void Canvas::SetPixel(const uint64_t x, const uint64_t y, const Pixel& pixel) noexcept{

    std::any_cast<CanvasImplementation*>(impl_)->SetPixel(x, y, pixel);

}


void Canvas::SetPixel(const uint64_t x, const uint64_t y, uint64_t size, const Pixel& pixel) noexcept {

    std::any_cast<CanvasImplementation*>(impl_)->SetPixel(x, y, size, pixel);

}

void Canvas::ChangeSize(const uint64_t width, const uint64_t height){

    std::any_cast<CanvasImplementation*>(impl_)->ChangeSize(width, height);

}

void Canvas::ChangePosition(const uint64_t x, const uint64_t y){

    std::any_cast<CanvasImplementation*>(impl_)->ChangePosition(x, y);

}

void Canvas::Fill(const Color& color) noexcept(true){

    std::any_cast<CanvasImplementation*>(impl_)->Fill(color);

}

void Canvas::Show(int nCmdShow){

    std::any_cast<CanvasImplementation*>(impl_)->Show(nCmdShow);

}

void Canvas::Destroy(){

    std::any_cast<CanvasImplementation*>(impl_)->Destroy();

}



void Canvas::Flush(){

    std::any_cast<CanvasImplementation*>(impl_)->Flush();

}

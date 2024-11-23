#pragma once
#include <unordered_map>
#include <raylib.h>
#include <vector>
#include <memory>
#include <string>

namespace pz {

	class Component {

	protected:		
		Rectangle rect{};
		float scale{ 1.0f };
		std::vector<std::unique_ptr<pz::Component>> children{};		

	public:				
		virtual ~Component() = default;
		
		virtual Vector2 get_center() const;
		virtual void set_center(float x, float y);

		virtual float get_centerx() const;
		virtual void set_centerx(float x);
		
		virtual float get_centery() const;
		virtual void set_centery(float y);

		virtual float get_left() const;
		virtual void set_left(float left);

		virtual float get_right() const;
		virtual void set_right(float right);
		
		virtual float get_top() const;
		virtual void set_top(float top);
		
		virtual float get_bottom() const;
		virtual void set_bottom(float bottom);

		virtual float width() const;
		virtual float height() const;
		
		virtual bool is_hovered() const;

		virtual Rectangle get_rect() const;		

		float get_scale() const;
		void set_scale(float scale);

		virtual pz::Component* add_component(std::unique_ptr<pz::Component> c);		

		virtual void update(float dt);
		virtual void draw();
	};

	class Border : public pz::Component {

	private:
		float thickness{1.0f};
		Color color{WHITE};

	public:
		Border() = default;
		Border(float thickness, Color color);
		Border(float thickness, Color color, Rectangle rect);
		float get_thickness() const;
		void set_thickness(float thickness);
		Color get_color() const;
		void set_color(const Color& color);		
		void set_rect(const Rectangle& rect);
		void draw() override;

	};

	class ImageComponent : public pz::Component {
	private:
		Texture2D texture{};
		std::string imagepath{};

	public:
		ImageComponent() = default;
		explicit ImageComponent(const char* filepath);
		const std::string& get_imagepath() const;
		const Texture& get_texture() const;
		void change_image(const char* filepath);
		void draw() override;
	};

	class ImageButton : public pz::Component {	

	private:		
		pz::ImageComponent* image;
		pz::ImageComponent* hover_image;
		void (*action)();

	public:
		ImageButton(
			const char* image,
			const char* hover_image,
			const float pos_x,
			const float pos_y,
			void (*action)()
		);
		void update(float dt) override;
		void draw() override;

	};


	class Grid : public pz::Component {

	private:
		int rows{};
		int columns{};
		float padding_x{};
		float padding_y{};
		float max_width{};
		float max_pos_x{};
		Rectangle last_component_rect{};
		Border border{3.0f, WHITE};
		pz::Component* hovered_component{nullptr};		

	public:
		Grid(
			int columns, 
			float pos_x,
			float pos_y,
			float padding_x, 
			float padding_y			
		);
		pz::Component* add_component(std::unique_ptr<pz::Component> c) override;
		pz::Component* get_hovered_component();
		void update(float dt) override;
		void move_horizontal(float delta);
		void move_vertical(float delta);
		void move(float delta_horizontal, float delta_vertical);
		void draw() override;
		void clear();

	};

}
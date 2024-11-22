#pragma once
#include <raylib.h>
#include <vector>
#include <memory>
#include <string>


namespace pz {

	class Component {

	protected:
		std::string name{};
		Rectangle rect{};
		float scale{ 1.0f };
		std::vector<std::unique_ptr<pz::Component>> children{};		

	public:
		Component() = default;
		Component(std::string name);
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

		virtual Rectangle get_rect() const;		

		float get_scale() const;
		void set_scale(float scale);

		virtual pz::Component* add_component(std::unique_ptr<pz::Component> c);

		const std::string& get_name() const;

		virtual void update(float dt);
		virtual void draw();
	};

	class Border : public pz::Component {

	private:
		float thickness{};
		Color color{};

	public:
		Border();
		Border(float thickness, Color color);
		Border(float thickness, Color color, Rectangle rect);
		float get_thickness() const;
		void set_thickness(float thickness);
		Color get_color() const;
		void set_color(const Color& color);		
		void set_rect(const Rectangle& rect);
		void draw() override;

	};

	class Image : public pz::Component {
	private:
		Texture2D texture{};		

	public:
		explicit Image(const char* filepath);
		~Image() override;
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
		const pz::Component* get_hovered_component() const;
		void update(float dt) override;
		void move_horizontal(float delta);
		void move_vertical(float delta);
		void move(float delta_horizontal, float delta_vertical);
		void draw() override;
		void clear();

	};

}
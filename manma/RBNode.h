#pragma once
#include <memory>

namespace rb_tree {
	enum class Color : int{
		Black,
		Red
	};

	template<typename T>
	class RBNode {
	public:
		explicit RBNode(const T& data);
		explicit RBNode(const std::unique_ptr<T>& data);
		explicit RBNode(const T& data, Color color);
		virtual ~RBNode() = default;

		virtual double getValue() const;
		virtual void copyData(const std::shared_ptr<RBNode<T>>& other);

		Color color;
		std::shared_ptr<RBNode> parent;
		std::shared_ptr<RBNode> left;
		std::shared_ptr<RBNode> right;
		std::unique_ptr<T> data;
	};

	template <typename T>
	RBNode<T>::RBNode(const T& data) : color(Color::Red), data{std::make_unique<T>(data)} {}

	template <typename T>
	RBNode<T>::RBNode(const std::unique_ptr<T>& data) : color(Color::Red), data{ std::move(data) } {}

	template <typename T>
	RBNode<T>::RBNode(const T& data, Color color) : color(color), data{ data } {}

	template <typename T>
	double RBNode<T>::getValue() const {
		return data->value;
	}

	template <typename T>
	void RBNode<T>::copyData(const std::shared_ptr<RBNode<T>>& other) {
		data = std::move(other->data);
	}

}


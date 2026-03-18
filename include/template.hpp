#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

class Template {
public:
    Template() = default;
    Template(const Template &) = default;
    Template(Template &&) = delete;
    Template &operator=(const Template &) = default;
    Template &operator=(Template &&) = delete;
    ~Template() = default;

    static void greet();
};

#endif // TEMPLATE_HPP

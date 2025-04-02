#pragma once

#include <string>
#include <string_view>

#include <ast_node_interface.hpp>

class Note: public ASTNodeInterface
{
public:
    Note() noexcept;

private:

};

class SimpleNote : public Note
{  
public:
    SimpleNote() noexcept;

    void destroy() noexcept override;
private:
    std::string note;
};

class DottedNote : public Note
{
public:
    DottedNote() noexcept;

    void destroy() noexcept override;
private:
    std::string dotted_note;
};

class RestNote : public Note
{   
public:
    RestNote() noexcept;

    void destroy() noexcept override;
private:
    std::string rest_note;
};

class AlteredNote : public Note
{
public:
    AlteredNote() noexcept;

    void destroy() noexcept override;
private:            
    std::string altered_note;
};
class AlteredDottedNote : public Note
{       
public:
    AlteredDottedNote() noexcept;

    void destroy() noexcept override;
private:
    std::string altered_dotted_note;
};


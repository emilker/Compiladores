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
    SimpleNote(std::string) noexcept;

    void destroy() noexcept override;
private:
    std::string note;
};

class DottedNote : public Note
{
public:
    DottedNote(std::string) noexcept;

    void destroy() noexcept override;
private:
    std::string dotted_note;
};
class AlteredNote : public Note
{
public:
    AlteredNote(std::string) noexcept;

    void destroy() noexcept override;
private:            
    std::string altered_note;
};
class AlteredDottedNote : public Note
{       
public:
    AlteredDottedNote(std::string) noexcept;

    void destroy() noexcept override;
private:
    std::string altered_dotted_note;
};


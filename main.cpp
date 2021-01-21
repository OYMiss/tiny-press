#include <iostream>
#include <filesystem>
#include <map>
#include <list>
#include "marktool/convert.h"
#include "html.h"

namespace fs = std::filesystem;

fs::path output_root;

void save(const std::string &content, const fs::path &path) {
    if (fs::exists(path.parent_path()) or fs::create_directories(path.parent_path())) {
        std::ofstream out;
        out.open(path);
        out << content;
        out.close();
    }
}

std::string trim(const std::string &s) {
    int i = 0;
    while (i < s.length() and s[i] == ' ') i++;
    auto j = s.length() - 1;
    while (j > i and s[j] == ' ') j--;
    return s.substr(i, j - i + 1);
}

void process_article_info(std::map<std::string, std::string> &info, std::ifstream &fin) {
    std::string buffer;
    bool info_begin = false;
    while (getline(fin, buffer)) {
        if (buffer.substr(0, 3) == "---") {
            if (info_begin) break;
            info_begin = true;
            continue;
        }
        int i = 0;
        while (i < buffer.length() and buffer[i] != ':') i++;
        if (buffer[i] == ':') {
            info[trim(buffer.substr(0, i))] = trim(buffer.substr(i + 1));
        }
    }
}

void generate_article(const Article *article, const fs::path &output_path) {
    save(cat_article_html(article), output_path);
}

void generate_archives(const std::list<const Article*> &article_list) {
    save(cat_archives_html(article_list), output_root / "archives" / "index.html");
}

void generate_categories(const std::map<std::string, std::list<const Article*>> &category_map) {
    std::list<std::string> category_list;
    for (auto [text, list] : category_map) {
        category_list.emplace_back(text);
        save(cat_category_articles_html(text, list), output_root / "categories" / text / "index.html");
    }
    save(cat_categories_html(category_list), output_root / "categories" / "index.html");
}

void generate_homepage(const std::list<const Article*> &article_list) {
    save(cat_homepage_html(article_list), output_root / "index.html");
}

bool compare_article_desc_by_date (const Article *first, const Article *second) {
    return first->date > second->date;
}

Article* process_markdown(const fs::path &entry_path, const fs::path &relative_path) {
    auto url = "/" / relative_path;
    std::ifstream fin(entry_path);
    std::map<std::string, std::string> info;
    // 处理分类、标题、日期等信息
    process_article_info(info, fin);
    auto article_pointer = new Article(info.at("title"), url, to_html(fin), info.at("categories"), info.at("date"));
    fin.close();
    return article_pointer;
}

void generate(const fs::path &path) {
    std::list<const Article*> article_list;
    std::map<std::string, std::list<const Article*>> category_map;

    for (const auto & entry : fs::recursive_directory_iterator(path)) {
        if (not entry.is_directory() and entry.path().extension() == ".md") {
            // 获取路径信息
            auto relative_path = entry.path().lexically_relative(path).replace_extension("");
            auto article_pointer = process_markdown(entry.path(), relative_path);
            article_list.push_back(article_pointer);
            category_map[article_pointer->category].push_back(article_pointer);

            // 生成文章详情页
            generate_article(article_pointer, output_root / relative_path / "index.html");
        }
    }

    article_list.sort(compare_article_desc_by_date);
    generate_homepage(article_list);
    generate_archives(article_list);
    generate_categories(category_map);
}

// tiny_press -i ./post/ -o /usr/local/var/www
int main (int argc, char const *argv[]) {
    fs::path path = "./post";
    output_root = "./output";

    if (argc == 2) {
        path = argv[1];
    } else {
        for (unsigned i = 1; i < argc; i++) {
            if (std::string(argv[i]) == "-o") {
                output_root = fs::path(argv[i + 1]);
            } else if (std::string(argv[i]) == "-i") {
                path = argv[i + 1];
            }
        }
    }
    if (not fs::exists(path)) {
        std::cout << "wrong path" << std::endl;
        exit(1);
    }
    generate(path);

    std::cout << "Current path is " << fs::current_path() << '\n';
    std::cout << "Input path is " << path << '\n';
    std::cout << "Output path is " << output_root << '\n';
}


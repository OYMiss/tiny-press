//
// Created by OYMiss on 2021/1/6.
//

#ifndef HTML_H
#define HTML_H

#include <map>

class Article {
public:
    std::string title;
    std::string url;
    std::string html;
    std::string category;
    std::string date;
    std::map<std::string, std::string> extras;

    Article(std::string title, std::string url, std::string html, std::string category, std::string date)
        : title(std::move(title)), url(std::move(url)), html(std::move(html)), category(std::move(category)), date(std::move(date)) {
    }
};

std::string cat_article_html(const Article *article);

std::string cat_homepage_html(const std::list<const Article*> &article_list);

std::string cat_archives_html(const std::list<const Article*> &article_list);

std::string cat_categories_html(const std::list<std::string> &category_list);

std::string cat_category_articles_html(const std::string &category_name, const std::list<const Article*> &article_list);

#endif //HTML_H

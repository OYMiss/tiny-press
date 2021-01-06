//
// Created by OYMiss on 2021/1/6.
//

#include <list>
#include <iostream>
#include "html.h"

std::string fill_link(const std::string &url) {
    return R"(<a class="fill-link" href=")" + url + "\"></a>";
}

std::string page_link(const std::string &text, const std::string &href) {
    return R"(<p class="page-link-container"><a href=")" + href + "\">" + text + "</a></p>";
}

std::string cat_homepage_item_html(const std::string &title, const std::string &content, const std::string &url) {
    return
            HOMEPAGE_ARTICLE_START +
            POST_HEAD_START + title + POST_HEAD_END +
            content +
            fill_link(url) +
            HOMEPAGE_ARTICLE_END;
}

std::string cat_content_html(const std::string &title, const std::string &content) {
    return
            HTML_START +
            HEAD_START + title + HEAD_END +
            BODY_START +
                HEADER +
                content +
            BODY_END +
            HTML_END;
}

std::string cat_markdown_page_html(const std::string &title, const std::string &content) {
    return cat_content_html(title,
                            ARTICLE_START +
                                POST_HEAD_START + title + POST_HEAD_END +
                                content +
                            ARTICLE_END);
}

std::string cat_page_html(const std::string &title, const std::string &content) {
    return cat_content_html(title,
                            PAGE_START +
                            PAGE_HEAD_START + title + PAGE_HEAD_END +
                            content +
                            PAGE_END);
}

std::string cat_homepage_html(const std::string &content) {
    return cat_content_html("Home",
                            HOMEPAGE_START +
                            content +
                            HOMEPAGE_END);
}
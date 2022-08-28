package main

import (
	"fmt"
	"github.com/gin-gonic/gin"
	"io/ioutil"
	"net/http"
	"regexp"
	"strconv"
)

var (
	usernameValidator = regexp.MustCompile("^[a-zA-Z0-9_]+$")
)

func validateUsername(username string) bool {
	return usernameValidator.MatchString(username)
}

func handlerHome(c *gin.Context) {
	articleLinks, err := GetArticleLinks()
	if err != nil {
		_ = c.AbortWithError(http.StatusInternalServerError, err)
		return
	}
	userLinks, err := GetUserLinks()
	if err != nil {
		_ = c.AbortWithError(http.StatusInternalServerError, err)
		return
	}
	renderHome(c, articleLinks, userLinks)
}

func handlerUserArticles(c *gin.Context) {
	username := c.Param("username")
	articleLinks, err := GetArticleLinksByUser(username)
	if err != nil {
		_ = c.AbortWithError(http.StatusInternalServerError, err)
		return
	}
	userLinks, err := GetUserLinks()
	if err != nil {
		_ = c.AbortWithError(http.StatusInternalServerError, err)
		return
	}
	renderUser(c, username, articleLinks, userLinks)
}

func handlerNew(c *gin.Context) {
	renderNew(c)
}

func handlerAbout(c *gin.Context) {
	renderAbout(c)
}

func handlerCreateArticle(c *gin.Context) {
	var b Article
	b.Name = c.PostForm("name")
	b.Username = c.PostForm("username")
	b.Brief = c.PostForm("brief")
	b.Content = c.PostForm("content")
	if b.Name == "" || b.Username == "" || b.Brief == "" || b.Content == "" {
		c.AbortWithStatus(http.StatusBadRequest)
		return
	}
	if !validateUsername(b.Username) {
		c.AbortWithStatus(http.StatusBadRequest)
		return
	}
	id, err := InsertNewArticle(b)
	if err != nil {
		_ = c.AbortWithError(http.StatusInternalServerError, err)
		return
	}
	c.Redirect(http.StatusFound, fmt.Sprintf("/article/%d", id))
}

func handlerEditArticle(c *gin.Context) {
	idStr := c.Param("id")
	id, err := strconv.Atoi(idStr)
	if err != nil {
		_ = c.AbortWithError(http.StatusBadRequest, err)
		return
	}
	article := Article{
		Id:       uint64(id),
		Name:     c.PostForm("name"),
		Username: c.PostForm("username"),
		Brief:    c.PostForm("brief"),
		Content:  c.PostForm("content"),
	}
	if article.Name == "" || article.Username == "" || article.Brief == "" || article.Content == "" {
		c.AbortWithStatus(http.StatusBadRequest)
		return
	}
	if !validateUsername(article.Username) {
		c.AbortWithStatus(http.StatusBadRequest)
		return
	}
	err = UpdateArticle(article)
	if err != nil {
		_ = c.AbortWithError(http.StatusInternalServerError, err)
		return
	}
	c.Redirect(http.StatusFound, fmt.Sprintf("/article/%d", article.Id))
}

func handlerPreview(c *gin.Context) {
	name := c.PostForm("name")
	username := c.PostForm("username")
	brief := c.PostForm("brief")
	content := c.PostForm("content")
	if name == "" || username == "" || brief == "" || content == "" {
		c.AbortWithStatus(http.StatusBadRequest)
		return
	}
	renderPreview(c, name, username, brief, content)
}

func handlerGetArticle(c *gin.Context) {
	idStr := c.Param("id")
	id, err := strconv.Atoi(idStr)
	if err != nil {
		_ = c.AbortWithError(http.StatusBadRequest, err)
		return
	}
	article, err := GetArticleByID(uint64(id))
	if err != nil {
		_ = c.AbortWithError(http.StatusInternalServerError, err)
		return
	}
	userLinks, err := GetUserLinks()
	if err != nil {
		_ = c.AbortWithError(http.StatusInternalServerError, err)
		return
	}
	renderArticle(c, *article, userLinks)
}

func handlerGetEditArticle(c *gin.Context) {
	idStr := c.Param("id")
	id, err := strconv.Atoi(idStr)
	if err != nil {
		_ = c.AbortWithError(http.StatusBadRequest, err)
		return
	}
	article, err := GetArticleByID(uint64(id))
	if err != nil {
		_ = c.AbortWithError(http.StatusInternalServerError, err)
		return
	}
	renderEdit(c, *article)
}

func handlerDeleteArticle(c *gin.Context) {
	idStr := c.Param("id")
	id, err := strconv.Atoi(idStr)
	if err != nil {
		_ = c.AbortWithError(http.StatusBadRequest, err)
		return
	}
	err = DeleteArticleByID(uint64(id))
	if err != nil {
		_ = c.AbortWithError(http.StatusInternalServerError, err)
		return
	}
	c.Redirect(http.StatusFound, "/")
}

func handlerFile(c *gin.Context, contentType, filename string) {
	file, err := ioutil.ReadFile(filename)
	if err != nil {
		_ = c.AbortWithError(http.StatusNotFound, err)
		return
	}
	c.Data(http.StatusOK, contentType, file)
}

func handlerFavicon(c *gin.Context) {
	handlerFile(c, "image/vnd.microsoft.com", "resources/favicon.ico")
}

func handlerStyle(c *gin.Context) {
	handlerFile(c, "text/css", "resources/style.css")
}

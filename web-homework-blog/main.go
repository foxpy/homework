package main

import (
	"github.com/gin-contrib/gzip"
	"github.com/gin-gonic/gin"
	"log"
)

func main() {
	router := gin.Default()
	router.Use(gzip.Gzip(gzip.DefaultCompression))
	router.LoadHTMLGlob("html/pages/*")

	router.GET("/favicon.ico", handlerFavicon)
	router.GET("/style.css", handlerStyle)

	router.GET("/", handlerHome)
	router.GET("/about", handlerAbout)
	router.GET("/new", handlerNew)
	router.GET("/article/:id", handlerGetArticle)
	router.GET("/edit/:id", handlerGetEditArticle)
	router.GET("/user/:username", handlerUserArticles)

	router.POST("/article", handlerCreateArticle)
	router.POST("/preview", handlerPreview)
	router.POST("/delete/:id", handlerDeleteArticle)
	router.POST("/edit/:id", handlerEditArticle)

	err := router.Run(":8080")
	if err != nil {
		log.Fatal(err.Error())
	}
}

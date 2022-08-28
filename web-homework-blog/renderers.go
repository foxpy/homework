package main

import (
	"github.com/gin-gonic/gin"
	"github.com/gomarkdown/markdown"
	"github.com/gomarkdown/markdown/parser"
	"github.com/microcosm-cc/bluemonday"
	"html/template"
	"net/http"
	"strings"
	"time"
)

var (
	footerTemplate = template.Must(template.ParseFiles("html/parts/footer.gohtml"))
	headerTemplate = template.Must(template.ParseFiles("html/parts/header.gohtml"))
)

func markdownContentToHTML(content string) template.HTML {
	md := markdown.NormalizeNewlines([]byte(content))
	p := parser.NewWithExtensions(parser.CommonExtensions | parser.HardLineBreak)
	unsafeHtml := markdown.ToHTML(md, p, nil)
	return template.HTML(bluemonday.UGCPolicy().SanitizeBytes(unsafeHtml))
}

func formatArticleLinksTime(articleLinks []Article) []gin.H {
	ret := make([]gin.H, len(articleLinks))
	for i := range articleLinks {
		ret[i] = gin.H{
			"Id":       articleLinks[i].Id,
			"Name":     articleLinks[i].Name,
			"Username": articleLinks[i].Username,
			"Date":     articleLinks[i].Date.Format(time.RFC822),
			"Brief":    articleLinks[i].Brief,
		}
	}
	return ret
}

func renderPart(tmpl *template.Template, data interface{}) template.HTML {
	ret := strings.Builder{}
	err := tmpl.Execute(&ret, data)
	if err != nil {
		panic(err.Error())
	}
	return template.HTML(ret.String())
}

func render(c *gin.Context, page string, pageData interface{}) {
	c.HTML(http.StatusOK, page, gin.H{
		"PageData": pageData,
		"Header":   renderPart(headerTemplate, gin.H{"Name": page}),
		"Footer":   renderPart(footerTemplate, nil),
	})
}

func renderHome(c *gin.Context, articleLinks []Article, userLinks []UserLink) {
	render(c, "home.gohtml", gin.H{
		"Articles": formatArticleLinksTime(articleLinks),
		"Users":    userLinks,
	})
}

func renderUser(c *gin.Context, username string, articleLinks []Article, userLinks []UserLink) {
	render(c, "user.gohtml", gin.H{
		"Username": username,
		"Articles": formatArticleLinksTime(articleLinks),
		"Users":    userLinks,
	})
}

func renderNew(c *gin.Context) {
	render(c, "new.gohtml", nil)
}

func renderAbout(c *gin.Context) {
	render(c, "about.gohtml", nil)
}

func renderPreview(c *gin.Context, name, username, brief, content string) {
	render(c, "preview.gohtml", gin.H{
		"Id":       0,
		"Name":     name,
		"Username": username,
		"Date":     time.Now().Format(time.RFC822),
		"Brief":    brief,
		"Content":  markdownContentToHTML(content),
	})
}

func renderArticle(c *gin.Context, b Article, userLinks []UserLink) {
	render(c, "article.gohtml", gin.H{
		"Article": gin.H{
			"Id":       b.Id,
			"Name":     b.Name,
			"Username": b.Username,
			"Date":     b.Date.Format(time.RFC822),
			"Brief":    b.Brief,
			"Content":  markdownContentToHTML(b.Content),
		},
		"Users": userLinks,
	})
}

func renderEdit(c *gin.Context, b Article) {
	render(c, "edit.gohtml", b)
}

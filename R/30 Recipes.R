suppressPackageStartupMessages(library(ggplot2))
suppressPackageStartupMessages(library(scales))

args <- commandArgs(TRUE)
choose <- strtoi(args[1])
path <- args[2]

cat(sprintf("Running 30 choose %d\n", choose))

CR <- read.csv(file("stdin"), header=T)

no_combs <- nrow(CR)

# plot graphs in pdf
m <- ggplot(CR, aes(x=x)) + geom_histogram(binwidth=5e-5)
m <- m + labs(list(title=sprintf("30 Choose %d\n(%d Combinations)", choose, no_combs), x="Conversion Rate", y="Count"))
m <- m + scale_x_continuous(labels=percent)

pdf(sprintf("%s/figs/30 choose %d.pdf", path, choose))
print(m)
invisible(dev.off())

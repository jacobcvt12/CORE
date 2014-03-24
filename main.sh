# remove first line, last column, AA, and sampled recipe
sed '1d' data/recipes.csv | cut -d'|' -f1-3 | grep -v '^AA' | shuf -n 30 > recipes.temp

combs=( 2 3 5 6 10 15 )

for comb in "${combs[@]}"
do
    cat recipes.temp | ./bin/calculate_CR $comb | Rscript ./R/30\ Recipes.R $comb $PWD
done

rm recipes.temp

echo "Done!"

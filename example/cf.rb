cf = ChangeFinder.new(5, 0.01, 10, 0.001, 10)

File.open('./misc/learning_data.tsv').each do |line|
  trend = line.chomp
  score = cf.score(trend.to_f)
  puts("Learning data.... #{trend}\t#{score}")
end

File.open('./example/result.tsv', 'w') do |f|
  File.open('./misc/ar.tsv').each do |line|
    trend = line.chomp
    score = cf.score(trend.to_f)
    puts("Analyzing data.... #{trend}\t#{score}")
    f.puts("#{trend}\t#{score}")
  end
end

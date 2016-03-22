cf = ChangeFinder.new(10, 0.01, 20, 0.001, 10)

File.open('./example/result.tsv', 'w') do |f|
  File.open('./misc/ar.tsv').each do |line|
    trend = line.chomp
    score = cf.score(trend.to_f)
    f.puts("#{trend}\t#{score}")
  end
end

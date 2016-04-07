##
## ChangeFinder Test
##

# ChangeFinder::SDAR class
assert "ChangeFinder::SDAR#next" do
  assert_equal 4.6622854710498, ChangeFinder::SDAR.new(3, 0.1).next(1).round(13)
end

assert "ChangeFinder::SDAR#prob" do
  assert_equal 0.39894228040143, ChangeFinder::SDAR.new(3, 0.1).prob(1, 1, 1).round(14)
end

assert "ChangeFinder::SDAR#score" do
  assert_equal 0.69314718055995, ChangeFinder::SDAR.new(3, 0.1).score(0.5).round(14)
end

assert 'ChangeFinder::SDAR#{dump, restore}' do
  cf = ChangeFinder::SDAR.new(3, 0.1)
  cf.next(0.5)

  d = cf.dump

  cf_dump = ChangeFinder::SDAR.new(3, 0.1)
  cf_dump.restore d

  assert_equal cf.next(0.1).round(14), cf_dump.next(0.1).round(14)
end

# ChangeFinder::Utils class
assert "ChangeFinder::Utils.smooth" do
  assert_equal 2, ChangeFinder::Utils.smooth([1,2,3], 3)
end

# ChangeFinder class
assert "ChangeFinder#score" do
  assert_equal 6.2017912433901, ChangeFinder.new(3, 0.1, 3, 0.1, 4).score(1).round(13)
end

assert "ChangeFinder#learn" do
  assert_equal [6.2017912433901, 2.7539626375604, 3.3137187076122], ChangeFinder.new(3, 0.1, 3, 0.1, 4).learn([1,1,1]).map{ |i| i.round(13)}
end

assert 'ChangeFinder#{dump, restore}' do
  cf = ChangeFinder.new(3, 0.1, 3, 0.1, 4)
  cf_dump = ChangeFinder.new(3, 0.1, 3, 0.1, 4)

  cf.score(5)

  assert_not_equal cf.dump, cf_dump.dump

  cf_dump.restore cf.dump

  assert_equal cf.dump, cf_dump.dump
  assert_equal cf.score(1).round(13), cf_dump.score(1).round(13)
end


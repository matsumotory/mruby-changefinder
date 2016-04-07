MRuby::Build.new do |conf|
  toolchain :gcc

  # include the default GEMs
  conf.gembox 'default'
  conf.gem File.expand_path(File.dirname(__FILE__))
  conf.enable_test
end


class ChangeFinder
  # ref: https://github.com/muddydixon/fluent-plugin-anomalydetect
  # thanks to @muddydixon
  class SDAR

    attr_reader :mu

    def initialize term, r
      @r = r
      @mu = 0
      @term = term
      @data = []
      @sigma = 0
      @c = (0..@term - 1).map { |i| rand }
    end

    def dump
      {:r => @r, :mu => @mu, :term => @term, :data => @data, :sigma => @sigma, :c => @c}
    end

    def restore params
      @r = params[:r]
      @mu = params[:mu]
      @term = params[:term]
      @data = params[:data].dup
      @sigma = params[:sigma]
      @c = params[:c]
    end

    def next x
      len = @data.size
      @mu = (1 - @r) * @mu + @r * x

      c = @sigma

      (0..(@term - 1)).each do |j|
        @c[j] = (1 - @r) * @c[j] + @r * (x - @mu) * (@data[len - 1 - j] - @mu) if @data[len - 1 - j]
      end

      cc = Matrix.zero(@term).to_a

      (0..(@term - 1)).each do |j|
        (j..(@term - 1)).each { |i| cc[j][i] = cc[i][j] = @c[i - j]}
      end

      w = (Matrix.rows(cc).inv * Vector.elements(@c)).to_a
      xt = @data.each_with_index.inject(@mu) { |sum, vidx| sum += w[vidx[1]] * (vidx[0] - @mu)}
      @sigma = (1 - @r) * @sigma + @r * (x - xt) * (x - xt)

      @data.push x
      @data.shift if @data.size > @term

      score(prob(xt, @sigma, x))
    end

    def prob mu, sigma, v
      return 0 if sigma.zero?
      Math.exp( - 0.5 * (v - mu) ** 2 / sigma) / ((2 * Math::PI) ** 0.5 * sigma ** 0.5)
    end

    def score p
      return 0 if p <= 0
      -Math.log(p)
    end

    def show_status
      {:sigma => @sigma, :mu => @mu, :data => @data, :c => @c}
    end
  end
end

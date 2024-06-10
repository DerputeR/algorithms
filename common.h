template <typename a>
void print_vec(const std::vector<a> &v)
{
    std::cout << "[";
    for (size_t i = 0; i < v.size(); i++)
    {
        std::cout << v[i];
        if (i + 1 < v.size())
        {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}
import { createRouter, createWebHistory } from 'vue-router'
import LoginForm from '../components/LoginForm.vue'

const routes = [
  {
    path: '/',
    name: 'login',
    component: LoginForm
  },
]

const router = createRouter({
  mode: 'history',
  history: createWebHistory(import.meta.env.BASE_URL),
  routes,
})

export default router
